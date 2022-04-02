#ifndef	DISCORD_CONTEXT_HPP__
#define DISCORD_CONTEXT_HPP__
/*
* ============================================================================================================
* Discord_Context
* 
* �۾��� : EavanKim
*
* �뵵 :
*	beginthreadex�� ���� �����Ǵ� Thread�� �Ѱ��ִ� Heap �޸� ���
*	������ Thread�� �������� ���.
*
* ���ǻ��� :
*	Thread ���������� ���� ����� ���� ���� ��.
*	�ϳ� �̻��� Thread�� �������̶�� Singleton�� ����ϰ� Thread-Safe���� ������ ��.
*	�Լ����� ����� �����縦 �ø��� ���� ���길 �� ����ϰ� �� ���� �޸𸮸� ����ϰ� �ǰ�
*	�޸𸮰� �� �ùٸ� ������ �������� �ִ��� ������ ��ư� ��
*	�ӽ��� ��ΰ� ����ؼ� �ذ��ϴ� ���� �ұԸ�� ����ϰԵǴ� '���� ������Ʈ'�� ���� �ƴϸ�,
*	���α׷��� �ϴ� ����� �ƴ϶� �����ڰ� ���α׷� ������ �� ������ ���⶧���� �����ڷμ� �ϴ� ���̶� ����
*
* �����ֱ� :
*	1. Context ������ Program ������
*	2. ������ Thread�� Program ������(���� �߻����� ���α׷� ���ᰡ �ʿ��� ��� ����� ������ ����)
*
* ============================================================================================================
*/

namespace Discord
{
	enum class CONTEXT_TYPE
	{
		UNKNOWN
		, SERVER
		, SESSION
		, WORK
		, MAX
	};

	class DContext
	{
	public:
		explicit DContext();
		explicit DContext(CONTEXT_TYPE _type);
		virtual ~DContext();

		CONTEXT_TYPE getType();

	private:
		CONTEXT_TYPE m_type;
	};
}

#endif