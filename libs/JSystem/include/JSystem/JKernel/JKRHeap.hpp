#ifndef JKR_HEAP_H
#define JKR_HEAP_H

#include <types.h>
#include <dolphin/os/OSMutex.h>
#include <JSystem/JKernel/JKRDisposer.hpp>
#include <new>

typedef void JKRHeapErrorHandler(void*, u32, int);

class JKRHeap : public JKRDisposer {
public:
	enum EAllocMode {
		HEAPALLOC_Unk1 = 1,
	};

public:
	JKRHeap(void* data, u32 size, JKRHeap* parent, bool errorFlag);

	bool setErrorFlag(bool errorFlag);

	virtual ~JKRHeap();
	virtual void* alloc(u32 size, int alignment) = 0;
	virtual void free(void* ptr)                 = 0;
	virtual void freeAll();
	virtual void freeTail()                 = 0;
	virtual s32 resize(void* ptr, u32 size) = 0;
	virtual s32 getSize(void* ptr)          = 0;
	virtual s32 getFreeSize()               = 0;
	virtual s32 getTotalFreeSize()          = 0;
	virtual u32 getHeapType()               = 0;
	virtual bool check()                    = 0;
	virtual bool dump() = 0;
	virtual s32 changeGroupID(u8 newGroupId);
	virtual u8 getCurrentGroupId();

	JKRHeap* becomeSystemHeap();
	JKRHeap* becomeCurrentHeap();
	void destroy();
	void fillFreeArea();
	static s32 getSize(void*, JKRHeap*);

	// TODO: pure speculation but helped JKRThread to match
	template <class T> static inline T* allocOne(int align, JKRHeap* heap)
	{
		return (T*)alloc(sizeof(T), align, heap);
	}

	// TODO: pure speculation but helped JKRThread to match
	template <class T>
	static inline T* allocArray(size_t cnt, int align, JKRHeap* heap)
	{
		return (T*)alloc(cnt * sizeof(T), align, heap);
	}

	// ... more functions

	void* getMaxFreeBlock();
	u32 getMaxAllocatableSize(int alignment);
	JKRHeap* find(void*) const;
	void dispose_subroutine(u32 begin, u32 end);
	bool dispose(void*, u32);
	void dispose(void*, void*);
	void dispose();

	void appendDisposer(JKRDisposer* disposer)
	{
		mDisposerList.append(&disposer->mPointerLinks);
	}

	void removeDisposer(JKRDisposer* disposer)
	{
		mDisposerList.remove(&disposer->mPointerLinks);
	}

	void* getStartAddr() const { return (void*)mStart; }
	void* getEndAddr() const { return (void*)mEnd; }
	u32 getHeapSize() const { return mSize; }
	bool getErrorFlag() const { return mErrorFlag; }
	void callErrorHandler(JKRHeap* heap, u32 size, int alignment)
	{
		if (mErrorHandler) {
			(*mErrorHandler)(heap, size, alignment);
		}
	}


	void lock() const { OSLockMutex(const_cast<OSMutex*>(&mMutex)); }
	void unlock() const { OSUnlockMutex(const_cast<OSMutex*>(&mMutex)); }

	JKRHeap* getParent() { return mChildTree.getParent()->getObject(); }

	const JSUTree<JKRHeap>& getHeapTree() { return mChildTree; }

	// Unused
	void checkMemoryFilled(u8*, u32 size, u8);

	static bool initArena(char**, u32*, int);
	static void* alloc(u32 byteCount, int padding, JKRHeap* heap);
	static void copyMemory(void* dst, void* src, u32 size);
	static void free(void*, JKRHeap*);
	static JKRHeap* findFromRoot(void*);

	static JKRHeap* getCurrentHeap() { return sCurrentHeap; }

	static JKRHeap* getRootHeap() { return sRootHeap; }

	static JKRHeap* getSystemHeap() { return sSystemHeap; }

	static JKRHeap* sSystemHeap;
	static JKRHeap* sCurrentHeap;
	static JKRHeap* sRootHeap;

	static JKRHeapErrorHandler* mErrorHandler;

protected:
	// _00 = vtable
	// _00-_18 = JKRDisposer
	OSMutex mMutex;                     // _18
	void* mStart;                       // _30
	void* mEnd;                         // _34
	u32 mSize;                          // _38
	JSUTree<JKRHeap> mChildTree;        // _3C
	JSUList<JKRDisposer> mDisposerList; // _58
	bool mErrorFlag;                    // _64
	bool mInitFlag;                     // _65
	u8 padding_0x6a[2];                 // _66
};

inline JKRHeap* JKRGetCurrentHeap() { return JKRHeap::getCurrentHeap(); }

inline JKRHeap* JKRGetSystemHeap() { return JKRHeap::getSystemHeap(); }

inline JKRHeap* JKRGetRootHeap() { return JKRHeap::getRootHeap(); }

inline void* JKRAllocFromSysHeap(u32 size, int alignment)
{
	return JKRHeap::getSystemHeap()->alloc(size, alignment);
}

inline void* JKRAllocFromHeap(JKRHeap* heap, u32 size, int alignment)
{
	return JKRHeap::alloc(size, alignment, heap);
}

inline void JKRFree(void* pBuf) { JKRHeap::free(pBuf, nullptr); }

inline void JKRFreeToHeap(JKRHeap* heap, void* ptr)
{
	JKRHeap::free(ptr, heap);
}

inline void JKRFreeToSysHeap(void* buf) { JKRHeap::getSystemHeap()->free(buf); }

void JKRDefaultMemoryErrorRoutine(void*, u32, int);

void* operator new(size_t);
void* operator new(size_t, int);
void* operator new(size_t, JKRHeap*, int);

void* operator new[](size_t);
void* operator new[](size_t, int);
void* operator new[](size_t, JKRHeap*, int);

void operator delete(void*);
void operator delete[](void*);

#endif
