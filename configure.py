#!/usr/bin/env python3

###
# Generates build files for the project.
# This file also includes the project configuration,
# such as compiler flags and the object matching status.
#
# Usage:
#   python3 configure.py
#   ninja
#
# Append --help to see available options.
###

import argparse
import sys
from pathlib import Path
from typing import Any, Dict, List

from tools.project import (
    Object,
    ProgressCategory,
    ProjectConfig,
    calculate_progress,
    generate_build,
    is_windows,
)

# Game versions
DEFAULT_VERSION = 0
VERSIONS = [
    "GLME01",  # USA (Rev 0)
    "GLMJ01",  # Japan
    "GLMP01_00", # PAL (Rev 0)
    "GLMP01_01", # PAL (Rev 1)
]

parser = argparse.ArgumentParser()
parser.add_argument(
    "mode",
    choices=["configure", "progress"],
    default="configure",
    help="script mode (default: configure)",
    nargs="?",
)
parser.add_argument(
    "-v",
    "--version",
    choices=VERSIONS,
    type=str.upper,
    default=VERSIONS[DEFAULT_VERSION],
    help="version to build",
)
parser.add_argument(
    "--build-dir",
    metavar="DIR",
    type=Path,
    default=Path("build"),
    help="base build directory (default: build)",
)
parser.add_argument(
    "--binutils",
    metavar="BINARY",
    type=Path,
    help="path to binutils (optional)",
)
parser.add_argument(
    "--compilers",
    metavar="DIR",
    type=Path,
    help="path to compilers (optional)",
)
parser.add_argument(
    "--map",
    action="store_true",
    help="generate map file(s)",
)
parser.add_argument(
    "--debug",
    action="store_true",
    help="build with debug info (non-matching)",
)
if not is_windows():
    parser.add_argument(
        "--wrapper",
        metavar="BINARY",
        type=Path,
        help="path to wibo or wine (optional)",
    )
parser.add_argument(
    "--dtk",
    metavar="BINARY | DIR",
    type=Path,
    help="path to decomp-toolkit binary or source (optional)",
)
parser.add_argument(
    "--objdiff",
    metavar="BINARY | DIR",
    type=Path,
    help="path to objdiff-cli binary or source (optional)",
)
parser.add_argument(
    "--sjiswrap",
    metavar="EXE",
    type=Path,
    help="path to sjiswrap.exe (optional)",
)
parser.add_argument(
    "--ninja",
    metavar="BINARY",
    type=Path,
    help="path to ninja binary (optional)",
)
parser.add_argument(
    "--verbose",
    action="store_true",
    help="print verbose output",
)
parser.add_argument(
    "--non-matching",
    dest="non_matching",
    action="store_true",
    help="builds equivalent (but non-matching) or modded objects",
)
parser.add_argument(
    "--warn",
    dest="warn",
    type=str,
    choices=["all", "off", "error"],
    help="how to handle warnings",
)
parser.add_argument(
    "--no-progress",
    dest="progress",
    action="store_false",
    help="disable progress calculation",
)
args = parser.parse_args()

config = ProjectConfig()
config.version = str(args.version)
version_num = VERSIONS.index(config.version)

# Apply arguments
config.build_dir = args.build_dir
config.dtk_path = args.dtk
config.objdiff_path = args.objdiff
config.binutils_path = args.binutils
config.compilers_path = args.compilers
config.generate_map = args.map
config.non_matching = args.non_matching
config.sjiswrap_path = args.sjiswrap
config.ninja_path = args.ninja
config.progress = args.progress
if not is_windows():
    config.wrapper = args.wrapper
# Don't build asm unless we're --non-matching
if not config.non_matching:
    config.asm_dir = None

# Tool versions
config.binutils_tag = "2.42-2"
config.compilers_tag = "20251118"
config.dtk_tag = "v1.8.3"
config.objdiff_tag = "v3.6.1"
config.sjiswrap_tag = "v1.2.2"
config.wibo_tag = "1.0.3"

# Project
config.config_path = Path("config") / config.version / "config.yml"
config.check_sha_path = Path("config") / config.version / "build.sha1"
config.asflags = [
    "-mgekko",
    "--strip-local-absolute",
    "-I include",
    f"-I build/{config.version}/include",
    f"--defsym BUILD_VERSION={version_num}",
]
config.ldflags = [
    "-fp hardware",
    "-nodefaults",
]
if args.debug:
    config.ldflags.append("-g")  # Or -gdwarf-2 for Wii linkers
if args.map:
    config.ldflags.append("-mapunused")
    # config.ldflags.append("-listclosure") # For Wii linkers

# Use for any additional files that should cause a re-configure when modified
config.reconfig_deps = []

# Optional numeric ID for decomp.me preset
# Can be overridden in libraries or objects
config.scratch_preset_id = None

# Base flags, common to most GC/Wii games.
# Generally leave untouched, with overrides added below.
cflags_base = [
    "-nodefaults",
    "-proc gekko",
    "-align powerpc",
    "-enum int",
    "-fp hardware",
    "-Cpp_exceptions off",
    "-O4,p",
    "-inline auto",
    '-pragma "cats off"',
    '-pragma "warn_notinlined off"',
    "-maxerrors 1",
    "-nosyspath",
    "-RTTI off",     # Only Gamecube/Wii game to actually use this
    "-fp_contract on",
    "-str reuse",
    "-multibyte",  # For Wii compilers, replace with `-enc SJIS`
    "-i include",
    "-i libs",
    "-i libs/PowerPC_EABI_Support/Runtime.PPCEABI.H/include",
    "-i libs/PowerPC_EABI_Support/MSL/MSL_C/MSL_Common/include",
    "-i libs/PowerPC_EABI_Support/MSL/MSL_C/MSL_Common_Embedded/include",
    "-i libs/TRK_MINNOW_DOLPHIN/include",
    "-i libs/PowerPC_EABI_Support/MSL/MSL_C++/MSL_Common/include",
    "-i libs/dolphin/include",
    "-i libs/hvqm4/include",
    "-i libs/JSystem/include",
    f"-i build/{config.version}/include",
    f"-DBUILD_VERSION={version_num}",
    f"-DVERSION={version_num}",
]

# Debug flags
if args.debug:
    # Or -sym dwarf-2 for Wii compilers
    cflags_base.extend(["-sym on", "-DDEBUG=1"])
else:
    cflags_base.append("-DNDEBUG=1")

# Warning flags
if args.warn == "all":
    cflags_base.append("-W all")
elif args.warn == "off":
    cflags_base.append("-W off")
elif args.warn == "error":
    cflags_base.append("-W error")

# Metrowerks library flags
cflags_metrowerks = [
    *cflags_base,
    "-use_lmw_stmw on",
    "-str reuse,pool,readonly",
    # "-gccinc",
    "-common off",
    "-inline deferred,auto",
]


cflags_metrowerks_trk = [
    "-nodefaults",
    "-proc gekko",
    "-align powerpc",
    "-enum int",
    "-fp hardware",
    "-Cpp_exceptions off",
    "-O4,p",
    "-inline on",
    '-pragma "cats off"',
    '-pragma "warn_notinlined off"',
    "-maxerrors 1",
    "-nosyspath",
    "-RTTI off",     # Only Gamecube/Wii game to actually use this
    "-fp_contract on",
    "-str reuse",
    "-multibyte",  # For Wii compilers, replace with `-enc SJIS`
    "-i include",
    "-i libs",
    "-i libs/PowerPC_EABI_Support/Runtime.PPCEABI.H/include",
    "-i libs/PowerPC_EABI_Support/MSL/MSL_C/MSL_Common/include",
    "-i libs/PowerPC_EABI_Support/MSL/MSL_C/MSL_Common_Embedded/include",
    "-i libs/TRK_MINNOW_DOLPHIN/include",
    "-i libs/PowerPC_EABI_Support/MSL/MSL_C++/MSL_Common/include",
    "-i libs/dolphin/include",
    "-i libs/hvqm4/include",
    "-i libs/JSystem/include",
    f"-i build/{config.version}/include",
    f"-DBUILD_VERSION={version_num}",
    f"-DVERSION={version_num}",
    "-O4,p", "-pool off", "-str readonly", "-enum min", "-sdatathreshold 0",
]

cflags_game = [
    *cflags_base,
    "-RTTI on",
    "-lang c++"
]

cflags_jsystem = [
    *cflags_base,
    "-RTTI on",
    "-lang c++"
]

# REL flags
cflags_rel = [
    *cflags_base,
    "-sdata 0",
    "-sdata2 0",
]

cflags_dolphin = [
    *cflags_base,
    "-fp_contract off",
]

config.linker_version = "GC/1.1"


# Helper function for Dolphin libraries
def DolphinLib(lib_name: str, objects: List[Object]) -> Dict[str, Any]:
    return {
        "lib": lib_name,
        "src_dir" : "libs/dolphin/src",
        "mw_version": "GC/1.1",
        "cflags": cflags_dolphin,
        "progress_category": "sdk",
        "objects": objects,
    }


# Helper function for REL script objects
def Rel(lib_name: str, objects: List[Object]) -> Dict[str, Any]:
    return {
        "lib": lib_name,
        "mw_version": "GC/1.3.2",
        "cflags": cflags_rel,
        "progress_category": "game",
        "objects": objects,
    }


# Helper function for Metroworks Libraries
def MetroworksLib(lib_name : str, objects: List[Object]) -> Dict[str, Any]:
    return {
        "lib": lib_name,
        "mw_version": config.linker_version,
        "cflags": cflags_metrowerks,
        "progress_category": "msl",
        "src_dir": "libs/",
        "objects": objects,
    }

def Trk_Minnow_Dolphin(objects: List[Object]) -> Dict[str, Any]:
    return {
        "lib": "TRK_MINNOW_DOLPHIN",
        "mw_version": "GC/1.1p1",
        "cflags": cflags_metrowerks_trk,
        "progress_category": "msl",
        "src_dir": "libs/",
        "objects": objects,
    }

def HVQM4(objects: List[Object]) -> Dict[str, Any]:
    return {
        "lib": "hvqm4dec",
        "mw_version": "GC/1.2.5",
        "cflags": cflags_base,
        "progress_category": "hvqm4",
        "src_dir": "libs/hvqm4/src/",
        "objects": objects,
    }


def JSystem(objects: List[Object]) -> Dict[str, Any]:
    return {
        "lib": "JSystem",
        "mw_version": "GC/1.2.5",
        "cflags": cflags_jsystem,
        "progress_category": "jsystem",
        "src_dir": "libs/JSystem/src/",
        "objects": objects,
    }


def Game(objects: List[Object]) -> Dict[str, Any]:
    return {
        "lib": "Game",
        "mw_version": config.linker_version,
        "cflags": cflags_game,
        "progress_category": "game",
        "src_dir": "src/",
        "objects": objects,
    }


Matching = True                   # Object matches and should be linked
NonMatching = False               # Object does not match and should not be linked
Equivalent = config.non_matching  # Object should be linked when configured with --non-matching


# Object is only matching for specific versions
def MatchingFor(*versions):
    return config.version in versions


config.warn_missing_config = True
config.warn_missing_source = False
config.libs = [

    JSystem([
        # Kernel
        Object(Matching, "JSystem/JKernel/JKRHeap.cpp"),
        Object(NonMatching, "JSystem/JKernel/JKRExpHeap.cpp"),
        Object(Matching, "JSystem/JKernel/JKRSolidHeap.cpp"),
        Object(Matching, "JSystem/JKernel/JKRDisposer.cpp"),
        Object(NonMatching, "JSystem/JKernel/JKRThread.cpp"),
        Object(NonMatching, "JSystem/JKernel/JKRAram.cpp"),


        Object(NonMatching, "JSystem/JKernel/JKRDecomp.cpp"),
        # Support
        Object(NonMatching, "JSystem/JSupport/JSUList.cpp"),

        # Utility
        Object(Matching, "JSystem/JUtility/JUTResource.cpp"),
        Object(Matching, "JSystem/JUtility/JUTTexture.cpp"),
        Object(Matching, "JSystem/JUtility/JUTPalette.cpp"),
        Object(NonMatching, "JSystem/JUtility/JUTDirectPrint.cpp"),
    ]),

    DolphinLib("base", [
        Object(Matching, "base/PPCArch.c")
    ]),

    DolphinLib("os", [
        Object(Matching, "os/OS.c"),
        Object(Matching, "os/OSAlarm.c"),
        Object(Matching, "os/OSAlloc.c"),
        Object(Matching, "os/OSArena.c"),
        Object(Matching, "os/OSAudioSystem.c"),
        Object(Matching, "os/OSCache.c"),
        Object(Matching, "os/OSContext.c"),
        Object(Matching, "os/OSError.c"),
        Object(Matching, "os/OSExi.c"),
        Object(Matching, "os/OSFont.c"),
        Object(Matching, "os/OSInterrupt.c"),
        Object(Matching, "os/OSLink.c"),
        Object(Matching, "os/OSMessage.c"),
        Object(Matching, "os/OSMutex.c"),
        Object(Matching, "os/OSReboot.c"),
        Object(Matching, "os/OSReset.c"),
        Object(Matching, "os/OSResetSW.c"),
        Object(Matching, "os/OSRtc.c"),
        Object(Matching, "os/OSSerial.c"),
        Object(Matching, "os/OSSync.c"),
        Object(Matching, "os/OSThread.c"),
        Object(Matching, "os/OSTime.c"),
        Object(Matching, "os/OSUartExi.c"),
        Object(Matching, "os/__start.c"),
        Object(Matching, "os/__ppc_eabi_init.c"),
    ]),

    DolphinLib("db", [
        Object(Matching, "db/db.c")
    ]),

    DolphinLib("mtx", [
        Object(Matching, "mtx/mtx.c"),
        Object(Matching, "mtx/mtx44.c"),
        Object(Matching, "mtx/vec.c"),
        Object(Matching, "mtx/mtxvec.c"),
    ]),

    DolphinLib("dvd", [
        Object(Matching, "dvd/dvdlow.c"),
        Object(Matching, "dvd/dvdfs.c"),
        Object(Matching, "dvd/dvd.c"),
        Object(Matching, "dvd/dvdqueue.c"),
        Object(Matching, "dvd/dvderror.c"),
        Object(Matching, "dvd/fstload.c"),
    ]),

    DolphinLib("vi", [
        Object(Matching, "vi/vi.c")
    ]),

    DolphinLib("pad", [
        Object(Matching, "pad/Padclamp.c"),
        Object(Matching, "pad/Pad.c")
    ]),

    DolphinLib("ai", [
        Object(Matching, "ai/ai.c")
    ]),

    DolphinLib("ar", [
        Object(Matching, "ar/ar.c"),
        Object(Matching, "ar/arq.c"),
    ]),

    DolphinLib("dsp", [
        Object(Matching, "dsp/dsp.c"),
    ]),

    DolphinLib("card", [
        Object(Matching, "card/CARDBios.c"),
        Object(Matching, "card/CARDRdwr.c"),
        Object(Matching, "card/CARDBlock.c"),
        Object(Matching, "card/CARDDir.c"),
        Object(Matching, "card/CARDCheck.c"),
        Object(Matching, "card/CARDMount.c"),
        Object(Matching, "card/CARDFormat.c"),
        Object(Matching, "card/CARDOpen.c"),
        Object(Matching, "card/CARDCreate.c"),
        Object(Matching, "card/CARDRead.c"),
        Object(Matching, "card/CARDWrite.c"),
        Object(Matching, "card/CARDStat.c"),
    ]),

    DolphinLib("gx", [
        Object(Matching, "gx/GXInit.c"),
        Object(Matching, "gx/GXFifo.c"),
        Object(Matching, "gx/GXAttr.c"),
        Object(Matching, "gx/GXMisc.c"),
        Object(Matching, "gx/GXGeometry.c"),
        Object(Matching, "gx/GXFrameBuf.c"),
        Object(Matching, "gx/GXLight.c"),
        Object(Matching, "gx/GXTexture.c"),
        Object(Matching, "gx/GXBump.c"),
        Object(Matching, "gx/GXTev.c"),
        Object(Matching, "gx/GXPixel.c"),
        Object(Matching, "gx/GXDraw.c"),
        Object(Matching, "gx/GXStubs.c"),
        Object(Matching, "gx/GXDisplayList.c"),
        Object(Matching, "gx/GXTransform.c"),
    ]),

    HVQM4([
        Object(Matching, "hvqm4dec/hvqm4dec.c"),
    ]),

    MetroworksLib("MSL_C", [
        Object(Matching, "PowerPC_EABI_Support/MSL/MSL_C/MSL_Common/src/abort_exit.c"),
        Object(NonMatching, "PowerPC_EABI_Support/MSL/MSL_C/MSL_Common/src/ansi_fp.c", extra_cflags=["-sym on"]),
        Object(Matching, "PowerPC_EABI_Support/MSL/MSL_C/MSL_Common/src/arith.c"),
        Object(Matching, "PowerPC_EABI_Support/MSL/MSL_C/MSL_Common/src/buffer_io.c"),
        Object(Matching, "PowerPC_EABI_Support/MSL/MSL_C/MSL_Common/src/ctype.c"),
        Object(Matching, "PowerPC_EABI_Support/MSL/MSL_C/MSL_Common/src/direct_io.c"),
        Object(Matching, "PowerPC_EABI_Support/MSL/MSL_C/MSL_Common/src/mbstring.c"),
        Object(Matching, "PowerPC_EABI_Support/MSL/MSL_C/MSL_Common/src/mem.c"),
        Object(Matching, "PowerPC_EABI_Support/MSL/MSL_C/MSL_Common/src/mem_funcs.c"),
        Object(Matching, "PowerPC_EABI_Support/MSL/MSL_C/MSL_Common/src/misc_io.c"),
        Object(Matching, "PowerPC_EABI_Support/MSL/MSL_C/MSL_Common/src/printf.c"),
        Object(Matching, "PowerPC_EABI_Support/MSL/MSL_C/MSL_Common/src/rand.c"),
        Object(Matching, "PowerPC_EABI_Support/MSL/MSL_C/MSL_Common/src/string.c"),
        Object(Matching, "PowerPC_EABI_Support/MSL/MSL_C/MSL_Common/src/scanf.c"),
        Object(Matching, "PowerPC_EABI_Support/MSL/MSL_C/MSL_Common/src/signal.c"),
        Object(Matching, "PowerPC_EABI_Support/MSL/MSL_C/MSL_Common/src/strtoul.c"),
        Object(Matching, "PowerPC_EABI_Support/MSL/MSL_C/MSL_Common/src/float.c"),
        Object(Matching, "PowerPC_EABI_Support/MSL/MSL_C/MSL_Common/src/uart_console_io.c"),
        Object(Matching, "PowerPC_EABI_Support/MSL/MSL_C/MSL_Common/src/wchar_io.c"),
    ]),

    MetroworksLib("Runtime.PPCEABI.H", [
        Object(Matching, "PowerPC_EABI_Support/Runtime.PPCEABI.H/src/global_destructor_chain.c"),
        Object(Matching, "PowerPC_EABI_Support/Runtime.PPCEABI.H/src/__init_cpp_exceptions.cpp"),
        Object(Matching, "PowerPC_EABI_Support/Runtime.PPCEABI.H/src/__va_arg.c"),
        Object(Matching, "PowerPC_EABI_Support/Runtime.PPCEABI.H/src/__mem.c"),
    ]),

    Trk_Minnow_Dolphin([
        Object(Matching, "TRK_MINNOW_DOLPHIN/src/debugger/embedded/MetroTRK/Portable/mainloop.c"),
        Object(Matching, "TRK_MINNOW_DOLPHIN/src/debugger/embedded/MetroTRK/Portable/nubevent.c"),
        Object(Matching, "TRK_MINNOW_DOLPHIN/src/debugger/embedded/MetroTRK/Portable/nubinit.c"),
        Object(Matching, "TRK_MINNOW_DOLPHIN/src/debugger/embedded/MetroTRK/Portable/msg.c"),
        Object(Matching, "TRK_MINNOW_DOLPHIN/src/debugger/embedded/MetroTRK/Portable/msgbuf.c"),
        Object(Matching, "TRK_MINNOW_DOLPHIN/src/debugger/embedded/MetroTRK/Portable/serpoll.c"),
        Object(Matching, "TRK_MINNOW_DOLPHIN/src/debugger/embedded/MetroTRK/Os/dolphin/usr_put.c"),
        Object(Matching, "TRK_MINNOW_DOLPHIN/src/debugger/embedded/MetroTRK/Portable/dispatch.c"),
        Object(Matching, "TRK_MINNOW_DOLPHIN/src/debugger/embedded/MetroTRK/Portable/msghndlr.c"),
        Object(NonMatching, "TRK_MINNOW_DOLPHIN/src/debugger/embedded/MetroTRK/Portable/support.c"),
        Object(Matching, "TRK_MINNOW_DOLPHIN/src/debugger/embedded/MetroTRK/Portable/mutex_TRK.c"),
        Object(Matching, "TRK_MINNOW_DOLPHIN/src/debugger/embedded/MetroTRK/Portable/notify.c"),
        Object(Matching, "TRK_MINNOW_DOLPHIN/src/debugger/embedded/MetroTRK/Processor/ppc/Generic/flush_cache.c"),
        Object(Matching, "TRK_MINNOW_DOLPHIN/src/debugger/embedded/MetroTRK/Portable/mem_TRK.c"),
        Object(Matching, "TRK_MINNOW_DOLPHIN/src/debugger/embedded/MetroTRK/Processor/ppc/Generic/targimpl.c"),
        Object(NonMatching, "TRK_MINNOW_DOLPHIN/src/__exception.s"),
        Object(Matching, "TRK_MINNOW_DOLPHIN/src/debugger/embedded/MetroTRK/Os/dolphin/dolphin_trk.c"),
        Object(Matching, "TRK_MINNOW_DOLPHIN/src/debugger/embedded/MetroTRK/Processor/ppc/Generic/mpc_7xx_603e.c"),
        Object(Matching, "TRK_MINNOW_DOLPHIN/src/debugger/embedded/MetroTRK/Portable/main_TRK.c"),
        Object(Matching, "TRK_MINNOW_DOLPHIN/src/debugger/embedded/MetroTRK/Os/dolphin/dolphin_trk_glue.c"),
        Object(Matching, "TRK_MINNOW_DOLPHIN/src/debugger/embedded/MetroTRK/Os/dolphin/targcont.c"),
    ]),

    DolphinLib("amcstubs", [
        Object(Matching, "amcstubs/AmcExi2Stubs.c")
    ]),

    Game([
        # Koga
        Object(Matching, "Koga/CharacterEventObserver.cpp"),
        Object(NonMatching, "Koga/Message.cpp"),
        # Unsorted
        Object(Matching, "Unsorted/staticData.cpp"),  # TODO Verify this is a seperate file

    ]),
]


# Optional callback to adjust link order. This can be used to add, remove, or reorder objects.
# This is called once per module, with the module ID and the current link order.
#
# For example, this adds "dummy.c" to the end of the DOL link order if configured with --non-matching.
# "dummy.c" *must* be configured as a Matching (or Equivalent) object in order to be linked.
def link_order_callback(module_id: int, objects: List[str]) -> List[str]:
    # Don't modify the link order for matching builds
    if not config.non_matching:
        return objects
    if module_id == 0:  # DOL
        return objects + ["dummy.c"]
    return objects


# Uncomment to enable the link order callback.
# config.link_order_callback = link_order_callback


# Optional extra categories for progress tracking
# Adjust as desired for your project
config.progress_categories = [
    ProgressCategory("game", "Game Code"),
    ProgressCategory("sdk", "SDK Code"),
    ProgressCategory("msl", "Metroworks Library Code"),
    ProgressCategory("hvqm4", "HVQM4 Library Code"),
    ProgressCategory("jsystem", "JSystem Code"),
]
config.progress_each_module = args.verbose
# Optional extra arguments to `objdiff-cli report generate`
config.progress_report_args = [
    # Marks relocations as mismatching if the target value is different
    # Default is "functionRelocDiffs=none", which is most lenient
    # "--config functionRelocDiffs=data_value",
]

if args.mode == "configure":
    # Write build.ninja and objdiff.json
    generate_build(config)
elif args.mode == "progress":
    # Print progress information
    calculate_progress(config)
else:
    sys.exit("Unknown mode: " + args.mode)
