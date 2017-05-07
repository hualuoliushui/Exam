#ifndef GSS_RBT_H
#define GSS_RBT_H
//����� Red Black Tree

namespace gss{

#define NIL nullptr
	/*
		�ڵ���ɫ-����ö��
	*/
	enum RBT_Node_Color
	{
		BLACK = 0,
		RED = 1
	};

	/*
		�ڵ�����-������
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

		//-----------------------------��ϵ-��������

		/*
		�游�ڵ�
		*/
		Node* grandparent(Node* n)
		{
			return n->parent->parent;
		}

		/*
		����ڵ�
		*/
		Node* uncle(Node* n)
		{
			if (n->parent == grandparent(n)->left)
				return grandparent(n)->right;
			else
				return grandparent(n)->left;
		}

		/*
		�ֵܽڵ�
		*/
		Node* sibling(Node* n){
			if (n == n->parent->left)
				return n->parent->right;
			else
				return n->parent->left;
		}

		//-----------------------------����-��������

		/*
			������������
		*/
		void delete_helper(Node* r){
			if (r == NIL)
				return;
			delete_helper(r->left);
			delete_helper(r->right);

			delete r;
			r = NIL;
		}

		//-----------------------------�ڵ���ת-��������

		/*
			����
		*/
		void rotate_left(Node* n)
		{
			Node* rc = n->right;	   // ��ʼ�� rc Ϊ n���Һ���
			n->right = rc->left;		   // ʹ rc ������Ϊ n���Һ���
			if (rc->left != NIL)
				rc->left->parent = n;	   // ��� rc �����Ӳ�Ϊ�ս�㣬�����丸�ڵ�Ϊ n
			rc->parent = n->parent;		   // ʹ rc�ĸ��ڵ�Ϊ n �ĸ��ڵ�
			if (n->parent == NIL)
				root = rc;				   // ʹ rc Ϊ���ĸ��ڵ�
			else if (n == n->parent->left)
				n->parent->left = rc;      // ʹ rc Ϊ n �ĸ��ڵ�����ӽ��
			else
				n->parent->right = rc;	   // ʹ rc Ϊ n �ĸ��ڵ���Һ��ӽ��
			rc->left = n;				   // ʹ n Ϊ rc ������
			n->parent = rc;				   // ʹ rc Ϊ n �ĸ��ڵ�
		}

		/*
			����
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

		//-----------------------------����-��������

		/*
			�½ڵ�Nλ�����ĸ��ڵ��ϣ�û�и��ڵ�
		*/
		void insert_case1(Node* n)
		{
			if (n->parent == NIL)
				n->color = BLACK;
			else
				insert_case2(n);
		}

		/*
			�½ڵ�ĸ��ڵ�P�Ǻ�ɫ
		*/
		void insert_case2(Node* n)
		{
			if (n->parent->color == BLACK)
				return;//����Ȼ��Ч
			else
				insert_case3(n);
		}

		/*
			���ڵ�P��������U����Ϊ��ɫ
		*/
		void insert_case3(Node* n)
		{
			if (uncle(n) != NIL && uncle(n)->color == RED){
				n->parent->color = BLACK;
				uncle(n)->color = BLACK;
				grandparent(n)->color = RED;
				insert_case1(grandparent(n));//��Ϊ�游�������Ǻ�ɫ�ģ�Υ������4���ݹ�����1
			}
			else
				insert_case4(n);//���������Ǻ�ɫ��
		}

		/*
			���ڵ�P�Ǻ�ɫ�ģ�������U�Ǻ�ɫ��NIL
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
			���ڵ�P�Ǻ�ɫ������ڵ�U�Ǻ�ɫ��NIL
		*/
		void insert_case5(Node* n)
		{
			n->parent->color = BLACK;
			grandparent(n)->color = RED;
			if (n == n->parent->left && n->parent == grandparent(n)->left){
				rotate_right(grandparent(n));
			}
			else //�������N���丸�ڵ���Һ��ӣ������ڵ�P�����丸�ڵ�G���Һ���
			{
				rotate_left(grandparent(n));
			}
		}

		//-----------------------------ɾ��-��������

		/*
			nΪ���ڵ㣬��n Ϊ ��ɫ��
		*/
		void remove_case1(Node* n)
		{
			if (n->parent == NIL)
			{
				//���nΪ���ڵ㣬ֱ�ӷ���
				return; //---------------------
			}
			// ������һ������
			remove_case2(n);
		}

		/*
			�ֵܽڵ� Ϊ ��ɫ���򣺸��ڵ� ��Ϊ ��ɫ,�ֵܽڵ�ĺ��ӽڵ� ��Ϊ ��ɫ
		*/
		void remove_case2(Node* n)
		{
			Node* s = sibling(n);
			
			if (s->color == RED) // �ֵܽڵ� Ϊ ��ɫ���򣺸��ڵ� ��Ϊ ��ɫ,�ֵܽڵ�ĺ��ӽڵ� ��Ϊ ��ɫ
			{
				n->parent->color = RED;
				s->color = BLACK;
				if (n == n->parent->left)
					rotate_left(n->parent);
				else
					rotate_right(n->parent);
				return; //----------------
			}
			// ������һ������
			remove_case3(n);
		}

		/*
			 �ֵܽڵ㼰�亢�ӽڵ㡢���ڵ� ��Ϊ ��ɫ
		*/
		void remove_case3(Node* n)
		{
			Node* s = sibling(n);

			if ((n->parent->color == BLACK) &&
				(s->color == BLACK) &&
				(s->left->color == BLACK) &&
				(s->right->color == BLACK))  // �ֵܽڵ㼰�亢�ӽڵ㡢���ڵ� ��Ϊ ��ɫ
			{
				s->color = RED;
				// �Ը��ڵ�Ϊ���� �����ĺ�ɫ�ڵ���Ŀ����һ���ݹ鴦���ڵ�
				remove_case1(n->parent);
				return; //-------------------
			}
			// ������һ������
			remove_case4(n);
		}

		/*
			�ֵܽڵ㼰�亢�ӽڵ� ��Ϊ ��ɫ�����ڵ� Ϊ ��ɫ
		*/
		void remove_case4(Node* n)
		{
			Node* s = sibling(n);

			if ((n->parent->color == RED) && 
				(s->color == BLACK) &&
				(s->left->color == BLACK) &&
				(s->right->color == BLACK)) // �ֵܽڵ㼰�亢�ӽڵ� ��Ϊ ��ɫ�����ڵ� Ϊ ��ɫ
			{
				s->color = RED;
				n->parent->color = BLACK;
				return; //--------------
			}
			// ������һ������
			remove_case5(n);
		}

		/*
			�ֵܽڵ�Ϊ��ɫ�����ֵܽڵ�ĺ��ӽڵ�� ��ɫ ����һ�� Ϊ ��ɫ
		*/
		void remove_case5(Node* n)
		{
			Node* s = sibling(n);

			if (s->color == BLACK) // �ֵܽڵ�Ϊ��ɫ
			{
				// ������µ��ֵܽڵ� �� �ֵܽڵ��һ�����ӽڵ�ͬ�� ���ң����ӣ���ɫ ��һ��

				if ((n == n->parent->left) &&
					(s->right->color == BLACK) &&
					(s->left->color == RED)) // �ֵܽڵ� Ϊ �Һ��ӣ��ֵܽڵ���Һ��� Ϊ ��ɫ������ Ϊ ��ɫ
				{
					// ������ �ֵܽڵ� ��Ϊ ��ɫ���ֵܽڵ������ ��Ϊ ��ɫ��ͬʱ���ֵܽڵ� ���� ����
					// ����� �µ��ֵܽڵ� Ϊ ��ɫ���ֵܽڵ���Һ��� Ϊ ��ɫ������ Ϊ ��ɫ
					s->color = RED;
					s->left->color = BLACK;
					rotate_right(s);
				}
				else if ((n == n->parent->right) &&
					(s->left->color == BLACK) &&
					(s->right->color == RED)) // �ֵܽڵ� Ϊ ���ӣ��ֵܽڵ������ Ϊ ��ɫ���Һ��� Ϊ ��ɫ
				{
					// ������ �ֵܽڵ� ��Ϊ ��ɫ���ֵܽڵ���Һ��� ��Ϊ ��ɫ��ͬʱ���ֵܽڵ� ���� ����
					// ����� �µ��ֵܽڵ� Ϊ ��ɫ���ֵܽڵ������ Ϊ ��ɫ���Һ��� Ϊ ��ɫ
					s->color = RED;
					s->right->color = BLACK;
					rotate_left(s);
				}
			}
			// ������һ������
			remove_case6(n);
		}

		/*
			�ֵܽڵ� Ϊ ��ɫ���ֵܽڵ� �� �ֵܽڵ��һ�����ӽڵ�ͬ�� ���ң����ӣ���ɫ ��һ��
		*/
		void remove_case6(Node* n)
		{
			Node* s = sibling(n);

			if (n == n->parent->left) // ��ǰ�ڵ� Ϊ ����
			{
				// �������� �ֵܽڵ���Һ��� ��Ϊ ��ɫ���Ը��ڵ� ���� ����
				s->right->color = BLACK;
				rotate_left(n->parent);
				return;//------------------
			}
			else // ��ǰ�ڵ� Ϊ �Һ���
			{
				// �������� �ֵܽڵ������ ��Ϊ ��ɫ���Ը��ڵ� ���� ����
				s->left->color = BLACK;
				rotate_right(n->parent);
				return;//------------------
			}
		}

	public:
		/*
			���캯��
		*/
		RBT()
			:root(NIL){};
		
		/*
			��������
		*/
		~RBT(){
			delete_helper(root);
		}

		/*
		ִ�в������
		*/
		void insert(Node* n)
		{
			Node* y = NIL;
			Node* x = root;
			//Ѱ�Ҳ����
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
			// �����ڵ� Ĭ��Ϊ��ɫ��������һ������
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
			ִ��ɾ������
		*/
		void remove(KEY key)
		{
			Node* y = NIL;
			Node* z = NIL;
			Node* p = NIL;
			Node* x = find(key);

			//�Ҳ���ָ��Ԫ��
			if (x == NIL)
				return; //--------------

			//Ѱ��������ɾ���Ľڵ�
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

			// �� x ��Ϊ������ɾ���Ľڵ�
			if (z != NIL)
			{
				//��ԭʼ��ɾ���Ľڵ�ʹ�� z �е����ݣ�����ֵ�����и���
				x->key = z->key;
				x->value = z->value;

				x = z; // 
			}

			// �� z ��Ϊƴ�������Ľڵ�
			if (x->left != NIL)
				z = x->left;
			else
				z = x->right;

			if (x->parent == NIL) // x Ϊ���ڵ㣬��ƴ�ӽڵ� z ����ɫ��Ϊ��ɫ����ָ��ָ��NIL��ֱ��ɾ�� x,����
			{
				if (z != NIL)
				{
					z->color = BLACK;
					z->parent = NIL;
				}
				root = z; // ���� �µĸ��ڵ�
				delete x;
				return; //------------------
			}
			else
			{
				p = x->parent;
				if (p->left == x) // x Ϊ����
				{
					p->left = z;
				}
				else // x Ϊ�Һ���
				{
					p->right = z;
				}

				if (x->color == RED) //�� ������ɾ���ڵ� x ����ɫΪ��ɫ���� z==NIL��ֱ��ɾ��x������
				{
					delete x;
					return; //---------------
				}

				//-------------- x ����ɫΪ��ɫ

				delete x; // ɾ��x
				x = NIL;

				if (z != NIL)
				{
					z->parent = p;

					if (z->color == RED) // �� ƴ�ӽڵ� z ����ɫΪ��ɫʱ��ֱ�ӽ� z ����ɫ��Ϊ ��ɫ������
					{
						z->color = BLACK;
						return; //--------------
					}
					else
					{
						// ZΪ��ɫ��z�ĸ��ڵ㲻ΪNIL���򣺱ش��� �ֵܽڵ� �� �ֵܽڵ�ĺ��ӽڵ�
						remove_case1(z);
					}

				}
			}
		}
	};
}

#endif