#ifndef GSS_HEAP_H
#define GSS_HEAP_H
#include <vector>

namespace gss
{
	/*
		Comp 仿函数对象，重载 operator()，参数为两个 NodeType 类型，返回 bool 类型
		仿函数使用时，需先实例化仿函数对象，再调用 operator()。
	*/
	template<typename NodeType, typename Comp>
	class Heap
	{
	private:
		// 成员变量
		std::vector<NodeType> _container;
		int _size;

		// 比较仿函数对象
		Comp _comp;
		// 交换
		void swap(int left, int right)
		{
			NodeType temp = _container[left];
			_container[left] = _container[right];
			_container[right] = temp;
		}
		// 修复堆-辅助函数
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
		// 是否为叶子节点
		bool isLeaf(int pos) const
		{
			return (pos >= _size / 2) && (pos < _size);
		}
		// 左节点的下标
		int leftchild(int pos) const
		{
			return 2 * pos + 1;
		}
		// 右节点的下标
		int rightchild(int pos) const
		{
			return 2 * pos + 2;
		}
		// 父节点的下标
		int parent(int pos) const
		{
			return (pos - 1) / 2;
		}
		// 创建堆-辅助函数
		void buildHeap()
		{
			for (int i = _size / 2 - 1; i >= 0; --i)
			{
				siftdown(i);
			}
		}

	public:
		// 构造函数
		Heap(std::vector<NodeType> container)
		{
			_container.assign(container.begin(),container.end());
			_size = _container.size();
			buildHeap();
		}
		// 元素数量
		int size() const
		{
			return _size;
		}
		// 插入操作
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
		// 堆顶元素
		NodeType top()
		{
			if (_size != 0)
				return _container[0];
			else
				return NULL;
		}
		// 删除堆顶元素
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
		// 删除指定位置的元素
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