#ifndef DISCORD_POINTER_HPP__
#define DISCORD_POINTER_HPP__

namespace Discord
{
	//�޸� �� �����ϰ� ��ư� �ּҰ� �������� ����� ������ ����
	//������� ����� ���� ����մϴ�.
	//���� ���� ����� �þ������
	//��Ȱ���� ���� ���� ���� ����� ������ �� �ִ� ��ü���� ����մϴ�.
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

	//shared���� ������ �����ؾ� ���ٵ� ���ذ� �����Ͽ� ����� �������� �ʾƼ� �켱 ��ü ���۷��� üũ�� ����մϴ�.
	//Dynamic üũ�� ����� �����Ƿ� �Ϻη� �����Ͽ����ϴ�.
	//������ InterlockedExchange���ԵǹǷ� ��뿡 ���Ǹ� ���մϴ�.
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