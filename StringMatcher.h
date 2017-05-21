#pragma once

namespace gss
{
#define STRINGMATCHER_M_TABLE_SIZE 256
	/*
	目前仅支持英文匹配
	*/
	class StringMatcher
	{
	protected:
		const char* m_ptr_pattern;
		const char* m_ptr_text;
		int m_size_pattern;
		int m_size_text;
	protected:
		virtual void init(){};
		virtual int run(){ return -1; };
	public:
		StringMatcher()
			:m_ptr_pattern(NULL), m_ptr_text(NULL) {};
		~StringMatcher(){};

		virtual const char* getName()
		{
			return "StringMatcher";
		}
		// 查找匹配，成功返回首次匹配的首字母下标，失败返回-1
		virtual int matching(const char* pattern, const char* text) final{
			if (pattern == NULL || text == NULL)
				return -1;
			m_ptr_pattern = pattern;
			m_ptr_text = text;
			m_size_pattern = strlen(m_ptr_pattern);
			m_size_text = strlen(m_ptr_text);

			init();
			return run();
		}
	};

	// KMP 算法
	class KMPMatcher :public StringMatcher
	{
	private:
		int* m_nextTable;

		void init_nextTable()
		{
			delete[] m_nextTable;
			m_nextTable = new int[m_size_pattern]();

			int q, k;// q：模板字符串下标；k：最大前后缀长度
			m_nextTable[0] = 0; // 模板字符串的第一个字符的最大前后缀长度为0

			for (q = 1, k = 0; q < m_size_pattern; ++q)//从第二个字符开始，依次计算每一个字符对应的next值
			{
				while (k > 0 && m_ptr_pattern[q] != m_ptr_pattern[k]) // 递归地求出m_ptr_pattern[0]...m_ptr_pattern[q]的最大的相同的前后缀长度k
					k = m_nextTable[k - 1];
				if (m_ptr_pattern[q] == m_ptr_pattern[k]) // 如果相等，那么最大相同前后缀长度加一
					++k;
				m_nextTable[q] = k;
			}
		}
	protected:
		void init()
		{
			init_nextTable();
		}

		int run()
		{
			int i, q;
			for (i = 0, q = 0; i < m_size_text; ++i)
			{
				while (q > 0 && m_ptr_pattern[q] != m_ptr_text[i])
				{
					q = m_nextTable[q - 1];
				}
				if (m_ptr_pattern[q] == m_ptr_text[i])
					++q;
				if (q == m_size_pattern)
					return (i - m_size_pattern + 1);
			}
			return -1;
		}
	public:
		KMPMatcher()
			:m_nextTable(NULL){}
		~KMPMatcher()
		{
			delete[] m_nextTable;
		}

		virtual const char* getName()
		{
			return "KMP";
		}
	};

	// Horspool 算法
	class HorspoolMatcher : public StringMatcher
	{
	private:
		int* m_badSymbolTable;

		void init_badSymbolTable()
		{
			delete[] m_badSymbolTable;
			m_badSymbolTable = new int[STRINGMATCHER_M_TABLE_SIZE]();
			for (int i = 0; i <= STRINGMATCHER_M_TABLE_SIZE - 1; ++i)
				m_badSymbolTable[i] = m_size_pattern;
			for (int j = 0; j <= m_size_pattern - 2; ++j)
				m_badSymbolTable[*(m_ptr_pattern + j)] = m_size_pattern - 1 - j;
			/*for (int i = 0; i < m_size_pattern; ++i)
			{
				std::cout << (*(m_ptr_pattern + i) - 0) << " ";
				if ((i + 1) % 10 == 0) std::cout << "\n";
			}*/
		}
	protected:
		void init()
		{
			init_badSymbolTable();
		}
		int run()
		{
			int i = m_size_pattern - 1, k;
			while (i <= m_size_text - 1)
			{
				k = 0;
				while (k <= m_size_pattern - 1 && m_ptr_pattern[m_size_pattern - 1 - k] == m_ptr_text[i - k])
				{
					++k;
				}
				if (k == m_size_pattern)
					return i - m_size_pattern + 1;
				else
					i += m_badSymbolTable[m_ptr_text[i]];
			}
			return -1;
		}
	public:
		HorspoolMatcher()
			:m_badSymbolTable(NULL){};
		~HorspoolMatcher()
		{
			delete[] m_badSymbolTable;
		}

		virtual const char* getName()
		{
			return "Horspool";
		}
	};

	// Boyer-Moore 算法
	class BoyerMooreMatcher :public StringMatcher
	{
	private:
		int* m_badSymbolTable;
		int* m_goodSuffixTable;

		void init_badSymbolTable()
		{
			delete[] m_badSymbolTable;
			m_badSymbolTable = new int[STRINGMATCHER_M_TABLE_SIZE]();
			for (int i = 0; i <= STRINGMATCHER_M_TABLE_SIZE - 1; ++i)
				m_badSymbolTable[i] = m_size_pattern;
			for (int j = 0; j <= m_size_pattern - 2; ++j)
				m_badSymbolTable[*(m_ptr_pattern + j)] = m_size_pattern - 1 - j;
		}

		void init_goodSuffixTable()
		{
			delete[] m_goodSuffixTable;
			m_goodSuffixTable = new int[m_size_pattern + 1]();
			int k, i, j;
			for (k = m_size_pattern - 1; k > 0; --k)
			{
				for (i = m_size_pattern - 2; i >= 0; --i)
				{
					for (j = i; j >= 0 && (i - j) <= (m_size_pattern - k) && m_ptr_pattern[j] == m_ptr_pattern[m_size_pattern - 1 - (i - j)]; --j);
					if (j < 0 || (i - j) >(m_size_pattern - k))
					{
						m_goodSuffixTable[m_size_pattern - k] = m_size_pattern - i - 1;
						i = -1;
						break;
					}
				}
			}
		}
	protected:
		void init()
		{
			init_badSymbolTable();
			init_goodSuffixTable();
		}
		int run()
		{
			int i = m_size_pattern - 1, k;
			while (i <= m_size_text - 1)
			{
				k = 0;
				while (k <= m_size_pattern - 1 && m_ptr_pattern[m_size_pattern - 1 - k] == m_ptr_text[i - k])
				{
					++k;
				}
				if (k == m_size_pattern)
					return i - m_size_pattern + 1;
				else
				{
					int d1 = m_badSymbolTable[m_ptr_text[i]] - k;
					d1 = d1 > 1 ? d1 : 1;
					if (k == 0)
						i += d1;
					else
					{
						int d2 = m_goodSuffixTable[k];
						i += d1 > d2 ? d1 : d2;
					}
				}
			}
			return -1;
		}
	public:
		BoyerMooreMatcher()
			:m_badSymbolTable(NULL), m_goodSuffixTable(NULL){};
		~BoyerMooreMatcher()
		{
			delete[] m_badSymbolTable;
			delete[] m_goodSuffixTable;
		}

		virtual const char* getName()
		{
			return "Boyer-Moore";
		}
	};

	class SundayMatcher :public StringMatcher
	{
	private:
		int* m_stepTable;

		void init_stepTable()
		{
			delete[] m_stepTable;
			m_stepTable = new int[STRINGMATCHER_M_TABLE_SIZE]();
			for (int i = 0; i < STRINGMATCHER_M_TABLE_SIZE; ++i)
				m_stepTable[i] = m_size_pattern + 1;
			for (int j = 0; j < m_size_pattern; ++j)
				m_stepTable[(unsigned char)m_ptr_pattern[j]] = m_size_pattern - j;
		}
	protected:
		void init()
		{
			init_stepTable();
		}
		int run()
		{
			int i_text = 0;
			int i_pattern = 0;
			while (i_text < m_size_text)
			{
				int temp = i_text;
				while (i_pattern < m_size_pattern)
				{
					if (m_ptr_text[i_text] == m_ptr_pattern[i_pattern])
					{
						++i_text;
						++i_pattern;
						continue;
					}
					else
					{
						if (temp + m_size_pattern>m_size_text)
							return -1;
						char firstRightChar = m_ptr_text[(temp + m_size_pattern)];
						i_text = temp + m_stepTable[(unsigned char)firstRightChar];
						i_pattern = 0;
						break;
					}
				}
				if (i_pattern == m_size_pattern)
					return i_text - m_size_pattern;
			}
			return -1;
		}
	public:
		SundayMatcher()
			:m_stepTable(NULL){};
		~SundayMatcher()
		{
			delete[] m_stepTable;
		}

		virtual const char* getName()
		{
			return "Sunday";
		}
	};
}