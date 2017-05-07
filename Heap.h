#ifndef GSS_HEAP_H
#define GSS_HEAP_H
#include <vector>

namespace gss
{
	/*
		Comp �º����������� operator()������Ϊ���� NodeType ���ͣ����� bool ����
		�º���ʹ��ʱ������ʵ�����º��������ٵ��� operator()��
	*/
	template<typename NodeType, typename Comp>
	class Heap
	{
	private:
		// ��Ա����
		std::vector<NodeType> _container;
		int _size;

		// �ȽϷº�������
		Comp _comp;
		// ����
		void swap(int left, int right)
		{
			NodeType temp = _container[left];
			_container[left] = _container[right];
			_container[right] = temp;
		}
		// �޸���-��������
		void siftdown(int pos)
		{
			while (!isLeaf(pos))
			{
				int j = leftchild(pos);
				int rc = rightchild(pos);
				if ((rc < _size)
					&& (_comp(_container[rc], _container[j])))
				{
					j = rc;
				}
				if (_comp(_container[pos], _container[j]))
					return;
				swap(pos, j);
				pos = j;
			}
		}
		// �Ƿ�ΪҶ�ӽڵ�
		bool isLeaf(int pos) const
		{
			return (pos >= _size / 2) && (pos < _size);
		}
		// ��ڵ���±�
		int leftchild(int pos) const
		{
			return 2 * pos + 1;
		}
		// �ҽڵ���±�
		int rightchild(int pos) const
		{
			return 2 * pos + 2;
		}
		// ���ڵ���±�
		int parent(int pos) const
		{
			return (pos - 1) / 2;
		}
		// ������-��������
		void buildHeap()
		{
			for (int i = _size / 2 - 1; i >= 0; --i)
			{
				siftdown(i);
			}
		}

	public:
		// ���캯��
		Heap(std::vector<NodeType> container)
		{
			_container.assign(container.begin(),container.end());
			_size = _container.size();
			buildHeap();
		}
		// Ԫ������
		int size() const
		{
			return _size;
		}
		// �������
		void insert(const NodeType& it)
		{
			int curr = _size;
			_container.push_back(it);
			++_size;

			while ((curr != 0)
				&& (_comp(_container[curr], _container[parent(curr)])))
			{
				swap(curr, parent(curr));
				curr = parent(curr);
			}
		}
		// �Ѷ�Ԫ��
		NodeType top()
		{
			if (_size != 0)
				return _container[0];
			else
				return NULL;
		}
		// ɾ���Ѷ�Ԫ��
		NodeType removeTop()
		{
			if (_size == 0)
				return NULL;
			int curr = _size;
			swap(0, _container[--curr]);
			if (curr != 0) 
				siftdown(0);
			NodeType temp = _container[curr];
			_container.pop_back();
			--_size;
			return temp;
		}
		// ɾ��ָ��λ�õ�Ԫ��
		NodeType remove(int pos)
		{
			int curr = _size;
			if (pos < 0 || pos >= curr)
				return NULL;
			if (pos == _size - 1)
			{
				--curr;
			}
			else
			{
				swap(pos, --curr);
				while ((pos!=0)
					&& (_comp(_container(pos), _container(parent(pos)))))
				{
					pos = parent(pos);
				}
				if (curr != 0)
					siftdown(curr);
			}
			NodeType temp = _container[curr];
			_container.pop_back();
			--_size;
			return temp;
		}
	};
}
#endif