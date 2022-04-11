#ifndef DISCORD_POINTER_HPP__
#define DISCORD_POINTER_HPP__

namespace Discord
{
	//메모리 상에 위험하고 어렵게 주소값 조작으로 헤더를 만들지 말고
	//상속으로 헤더를 만들어서 사용합니다.
	//생성 해제 비용이 늘어나겠지만
	//재활용을 통해 생성 해제 비용을 절약할 수 있는 객체에만 사용합니다.
	class DRefClass
	{
	public:
		explicit DRefClass();
		virtual ~DRefClass();
		void Reference_Count_Increase();
		void Reference_Count_Decrease();
		DINT_T Get_Reference_Count();

	private:
		DINT_T m_referenceCount = 0;
	};

	union DPtr
	{
		DRefClass* read;
		DINT_PTR_T interlockingUpdate;
	};

	//shared에서 수행이 가능해야 할텐데 이해가 부족하여 제대로 동작하지 않아서 우선 자체 레퍼런스 체크를 사용합니다.
	//Dynamic 체크는 비용이 높으므로 일부러 제외하였습니다.
	//강제로 InterlockedExchange대입되므로 사용에 주의를 요합니다.
	template<class C = DRefClass>
	class DRef_Ptr
	{
	public:
		explicit DRef_Ptr<C>();
		explicit DRef_Ptr<C>(C* _ptr);
		explicit DRef_Ptr<C>(DRef_Ptr<C>& _ptr);
		explicit DRef_Ptr<C>(DRef_Ptr<C>&& _ptr);
		~DRef_Ptr<C>();

		DINT_T tryDestroy();
		void set(C* _ptr);
		void set(DRef_Ptr<C>& _ptr);
		C* get();
		C* operator*();
		virtual void operator=(C* _ptr);
		virtual void operator=(DRef_Ptr<C>& _ptr);

	private:
		DPtr m_ptr = {};
	};

	template<class C>
	inline DRef_Ptr<C>::DRef_Ptr()
	{
		set(0);
	}

	template<class C>
	inline DRef_Ptr<C>::DRef_Ptr(C* _ptr)
	{
		set(_ptr);
	}

	template<class C>
	inline DRef_Ptr<C>::DRef_Ptr(DRef_Ptr<C>& _ptr)
	{
		set(_ptr);
	}

	template<class C>
	inline DRef_Ptr<C>::DRef_Ptr(DRef_Ptr<C>&& _ptr)
	{
		set(_ptr);
	}

	template<class C>
	inline DRef_Ptr<C>::~DRef_Ptr()
	{
		tryDestroy();
	}

	template<class C>
	inline DINT_T DRef_Ptr<C>::tryDestroy()
	{
		if (nullptr == m_ptr.read)
			return 0;

		OutputDebugStringW(DPrintf(L"ReferenceCheck : %d \n", m_ptr.read->Get_Reference_Count()).c_str());

		m_ptr.read->Reference_Count_Decrease();

		if (0 == m_ptr.read->Get_Reference_Count())
		{
			delete m_ptr.read;
			m_ptr.read = nullptr;
			return 0;
		}

		DINT_T Result = m_ptr.read->Get_Reference_Count();

#ifndef _WIN64
		InterlockedExchange(&(m_ptr.interlockingUpdate), 0);
#else
		InterlockedExchange64(&(m_ptr.interlockingUpdate), 0);
#endif

		return Result;
	}

	template<class C>
	inline void DRef_Ptr<C>::set(C* _ptr)
	{
		tryDestroy();
#ifndef _WIN64
		InterlockedExchange(&(m_ptr.interlockingUpdate), (__int32)_ptr);
#else
		InterlockedExchange64(&(m_ptr.interlockingUpdate), (__int64)_ptr);
#endif
		if (nullptr != m_ptr.read)
			m_ptr.read->Reference_Count_Increase();
	}

	template<class C>
	inline void DRef_Ptr<C>::set(DRef_Ptr<C>& _ptr)
	{
		tryDestroy();
#ifndef _WIN64
		InterlockedExchange(&(m_ptr.interlockingUpdate), _ptr.m_ptr.interlockingUpdate);
#else
		InterlockedExchange64(&(m_ptr.interlockingUpdate), _ptr.m_ptr.interlockingUpdate);
#endif
		if (nullptr != m_ptr.read)
			m_ptr.read->Reference_Count_Increase();
	}

	template<class C>
	inline C* DRef_Ptr<C>::get()
	{
		return reinterpret_cast<C*>(m_ptr.read);
	}

	template<class C>
	inline C* DRef_Ptr<C>::operator*()
	{
		return reinterpret_cast<C*>(m_ptr.read);
	}

	template<class C>
	inline void DRef_Ptr<C>::operator=(C* _ptr)
	{
		set(_ptr);
	}

	template<class C>
	inline void DRef_Ptr<C>::operator=(DRef_Ptr<C>& _ptr)
	{
		set(_ptr);
	}
}

#endif // !DISCORD_POINTER_HPP__