#ifndef GSS_RBT_H
#define GSS_RBT_H
//红黑树 Red Black Tree

namespace gss{

#define NIL nullptr
	/*
		节点颜色-辅助枚举
	*/
	enum RBT_Node_Color
	{
		BLACK = 0,
		RED = 1
	};

	/*
		节点类型-辅助类
	*/
	template <typename KEY, typename VALUE>
	class RBT_Node
	{
	public:
		RBT_Node()
			:parent(NIL), left(NIL), right(NIL)
		{};
		RBT_Node(KEY k, VALUE v)
			:parent(NIL), left(NIL), right(NIL), key(k), value(v)
		{};

		~RBT_Node(){};

		RBT_Node* parent;
		RBT_Node* left;
		RBT_Node* right;
		RBT_Node_Color color;
		KEY key;
		VALUE value;
	};

	template <typename KEY, typename VALUE>
	class RBT
	{
	public:
		typedef typename RBT_Node<KEY, VALUE> Node;
	private:
		Node* root;

		//-----------------------------关系-辅助函数

		/*
		祖父节点
		*/
		Node* grandparent(Node* n)
		{
			return n->parent->parent;
		}

		/*
		叔叔节点
		*/
		Node* uncle(Node* n)
		{
			if (n->parent == grandparent(n)->left)
				return grandparent(n)->right;
			else
				return grandparent(n)->left;
		}

		/*
		兄弟节点
		*/
		Node* sibling(Node* n){
			if (n == n->parent->left)
				return n->parent->right;
			else
				return n->parent->left;
		}

		//-----------------------------析构-辅助函数

		/*
			辅助析构函数
		*/
		void delete_helper(Node* r){
			if (r == NIL)
				return;
			delete_helper(r->left);
			delete_helper(r->right);

			delete r;
			r = NIL;
		}

		//-----------------------------节点旋转-辅助函数

		/*
			左旋
		*/
		void rotate_left(Node* n)
		{
			Node* rc = n->right;	   // 初始化 rc 为 n的右孩子
			n->right = rc->left;		   // 使 rc 的左孩子为 n的右孩子
			if (rc->left != NIL)
				rc->left->parent = n;	   // 如果 rc 的左孩子不为空结点，设置其父节点为 n
			rc->parent = n->parent;		   // 使 rc的父节点为 n 的父节点
			if (n->parent == NIL)
				root = rc;				   // 使 rc 为树的根节点
			else if (n == n->parent->left)
				n->parent->left = rc;      // 使 rc 为 n 的父节点的左孩子结点
			else
				n->parent->right = rc;	   // 使 rc 为 n 的父节点的右孩子结点
			rc->left = n;				   // 使 n 为 rc 的左孩子
			n->parent = rc;				   // 使 rc 为 n 的父节点
		}

		/*
			右旋
		*/
		void rotate_right(Node* n)
		{
			Node* lc = n->left;
			n->left = lc->right;
			if (lc->right != NIL)
				lc->right->parent = n;
			lc->parent = n->parent;
			if (n->parent == NIL)
				root = lc;
			else if (n == n->parent->left)
				n->parent->left = lc;
			else
				n->parent->right = lc;
			lc->right = n;
			n->parent = lc;
		}

		//-----------------------------插入-辅助函数

		/*
			新节点N位于树的根节点上，没有父节点
		*/
		void insert_case1(Node* n)
		{
			if (n->parent == NIL)
				n->color = BLACK;
			else
				insert_case2(n);
		}

		/*
			新节点的父节点P是黑色
		*/
		void insert_case2(Node* n)
		{
			if (n->parent->color == BLACK)
				return;//树仍然有效
			else
				insert_case3(n);
		}

		/*
			父节点P、叔叔结点U，都为红色
		*/
		void insert_case3(Node* n)
		{
			if (uncle(n) != NIL && uncle(n)->color == RED){
				n->parent->color = BLACK;
				uncle(n)->color = BLACK;
				grandparent(n)->color = RED;
				insert_case1(grandparent(n));//因为祖父结点可能是红色的，违反性质4，递归情形1
			}
			else
				insert_case4(n);//否则，叔叔是黑色的
		}

		/*
			父节点P是红色的，叔叔结点U是黑色或NIL
		*/
		void insert_case4(Node* n)
		{
			if (n == n->parent->right && n->parent == grandparent(n)->left){
				rotate_left(n->parent);
				n = n->left;
			}
			else if (n == n->parent->left && n->parent == grandparent(n)->right){
				rotate_right(n->parent);
				n = n->right;
			}
			insert_case5(n);
		}

		/*
			父节点P是红色，叔叔节点U是黑色或NIL
		*/
		void insert_case5(Node* n)
		{
			n->parent->color = BLACK;
			grandparent(n)->color = RED;
			if (n == n->parent->left && n->parent == grandparent(n)->left){
				rotate_right(grandparent(n));
			}
			else //反情况，N是其父节点的右孩子，而父节点P又是其父节点G的右孩子
			{
				rotate_left(grandparent(n));
			}
		}

		//-----------------------------删除-辅助函数

		/*
			n为根节点，（n 为 黑色）
		*/
		void remove_case1(Node* n)
		{
			if (n->parent == NIL)
			{
				//如果n为根节点，直接返回
				return; //---------------------
			}
			// 进行下一步调整
			remove_case2(n);
		}

		/*
			兄弟节点 为 红色，则：父节点 必为 黑色,兄弟节点的孩子节点 必为 黑色
		*/
		void remove_case2(Node* n)
		{
			Node* s = sibling(n);
			
			if (s->color == RED) // 兄弟节点 为 红色，则：父节点 必为 黑色,兄弟节点的孩子节点 必为 黑色
			{
				n->parent->color = RED;
				s->color = BLACK;
				if (n == n->parent->left)
					rotate_left(n->parent);
				else
					rotate_right(n->parent);
				return; //----------------
			}
			// 进行下一步调整
			remove_case3(n);
		}

		/*
			 兄弟节点及其孩子节点、父节点 均为 黑色
		*/
		void remove_case3(Node* n)
		{
			Node* s = sibling(n);

			if ((n->parent->color == BLACK) &&
				(s->color == BLACK) &&
				(s->left->color == BLACK) &&
				(s->right->color == BLACK))  // 兄弟节点及其孩子节点、父节点 均为 黑色
			{
				s->color = RED;
				// 以父节点为根的 子树的黑色节点数目减少一，递归处理父节点
				remove_case1(n->parent);
				return; //-------------------
			}
			// 进入下一步调整
			remove_case4(n);
		}

		/*
			兄弟节点及其孩子节点 均为 黑色，父节点 为 红色
		*/
		void remove_case4(Node* n)
		{
			Node* s = sibling(n);

			if ((n->parent->color == RED) && 
				(s->color == BLACK) &&
				(s->left->color == BLACK) &&
				(s->right->color == BLACK)) // 兄弟节点及其孩子节点 均为 黑色，父节点 为 红色
			{
				s->color = RED;
				n->parent->color = BLACK;
				return; //--------------
			}
			// 进入下一步调整
			remove_case5(n);
		}

		/*
			兄弟节点为黑色，且兄弟节点的孩子节点的 颜色 至少一个 为 红色
		*/
		void remove_case5(Node* n)
		{
			Node* s = sibling(n);

			if (s->color == BLACK) // 兄弟节点为黑色
			{
				// 结果：新的兄弟节点 与 兄弟节点的一个孩子节点同属 左（右）孩子，颜色 不一致

				if ((n == n->parent->left) &&
					(s->right->color == BLACK) &&
					(s->left->color == RED)) // 兄弟节点 为 右孩子，兄弟节点的右孩子 为 黑色，左孩子 为 红色
				{
					// 调整： 兄弟节点 设为 红色，兄弟节点的左孩子 设为 黑色，同时对兄弟节点 进行 右旋
					// 结果： 新的兄弟节点 为 黑色，兄弟节点的右孩子 为 红色，左孩子 为 黑色
					s->color = RED;
					s->left->color = BLACK;
					rotate_right(s);
				}
				else if ((n == n->parent->right) &&
					(s->left->color == BLACK) &&
					(s->right->color == RED)) // 兄弟节点 为 左孩子，兄弟节点的左孩子 为 黑色，右孩子 为 红色
				{
					// 调整： 兄弟节点 设为 红色，兄弟节点的右孩子 设为 黑色，同时对兄弟节点 进行 左旋
					// 结果： 新的兄弟节点 为 黑色，兄弟节点的左孩子 为 红色，右孩子 为 黑色
					s->color = RED;
					s->right->color = BLACK;
					rotate_left(s);
				}
			}
			// 进入下一步调整
			remove_case6(n);
		}

		/*
			兄弟节点 为 黑色，兄弟节点 与 兄弟节点的一个孩子节点同属 左（右）孩子，颜色 不一致
		*/
		void remove_case6(Node* n)
		{
			Node* s = sibling(n);

			if (n == n->parent->left) // 当前节点 为 左孩子
			{
				// 调整：将 兄弟节点的右孩子 设为 黑色，对父节点 进行 左旋
				s->right->color = BLACK;
				rotate_left(n->parent);
				return;//------------------
			}
			else // 当前节点 为 右孩子
			{
				// 调整：将 兄弟节点的左孩子 设为 黑色，对父节点 进行 右旋
				s->left->color = BLACK;
				rotate_right(n->parent);
				return;//------------------
			}
		}

	public:
		/*
			构造函数
		*/
		RBT()
			:root(NIL){};
		
		/*
			析构函数
		*/
		~RBT(){
			delete_helper(root);
		}

		/*
		执行插入操作
		*/
		void insert(Node* n)
		{
			Node* y = NIL;
			Node* x = root;
			//寻找插入点
			while (x != NIL)
			{
				y = x;
				if (n->key < x->key)
					x = x->left;
				else
					x = x->right;
			}
			n->parent = y;
			if (y == NIL)
				root = n;
			else if (n->key < y->key)
				y->left = n;
			else
				y->right = n;
			n->left = NIL;
			n->right = NIL;
			n->color = RED;
			// 新增节点 默认为红色，进行下一步调整
			insert_case1(n);
		}

		Node* find(KEY key)
		{
			Node* x = root;
			while (x != NIL && x->key != key)
			{
				if (x->key < key){
					x = x->right;
				}
				else if (x->key> key)
				{
					x = x->left;
				}
			}
			return x;
		}

		/*
			执行删除操作
		*/
		void remove(KEY key)
		{
			Node* y = NIL;
			Node* z = NIL;
			Node* p = NIL;
			Node* x = find(key);

			//找不到指定元素
			if (x == NIL)
				return; //--------------

			//寻找真正待删除的节点
			if (x->left == NIL)
			{
				y = x->right;
				z = y;
				while (y != NIL)
				{
					z = y;
					y = y->left;
				}
			}
			else
			{
				y = x->left;
				z = y;
				while (y != NIL)
				{
					z = y;
					y = y->right;
				}
			}

			// 将 x 设为真正待删除的节点
			if (z != NIL)
			{
				//将原始待删除的节点使用 z 中的数据（键，值）进行覆盖
				x->key = z->key;
				x->value = z->value;

				x = z; // 
			}

			// 将 z 设为拼接上来的节点
			if (x->left != NIL)
				z = x->left;
			else
				z = x->right;

			if (x->parent == NIL) // x 为根节点，将拼接节点 z 的颜色设为黑色、父指针指向NIL，直接删除 x,返回
			{
				if (z != NIL)
				{
					z->color = BLACK;
					z->parent = NIL;
				}
				root = z; // 设置 新的根节点
				delete x;
				return; //------------------
			}
			else
			{
				p = x->parent;
				if (p->left == x) // x 为左孩子
				{
					p->left = z;
				}
				else // x 为右孩子
				{
					p->right = z;
				}

				if (x->color == RED) //当 真正待删除节点 x 的颜色为红色，则 z==NIL，直接删除x，返回
				{
					delete x;
					return; //---------------
				}

				//-------------- x 的颜色为黑色

				delete x; // 删除x
				x = NIL;

				if (z != NIL)
				{
					z->parent = p;

					if (z->color == RED) // 当 拼接节点 z 的颜色为红色时，直接将 z 的颜色设为 黑色，返回
					{
						z->color = BLACK;
						return; //--------------
					}
					else
					{
						// Z为黑色，z的父节点不为NIL，则：必存在 兄弟节点 和 兄弟节点的孩子节点
						remove_case1(z);
					}

				}
			}
		}
	};
}

#endif