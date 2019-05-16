#include<stdio.h>
#include<stdlib.h>
#define MAX_SIZE 100
struct tnode
{
  int data;
  struct tnode *left;
  struct tnode *right;
};

void Insert(struct tnode**,int);
void preorder(struct tnode *t);
void inorder(struct tnode *t);
void postorder(struct tnode *t);

int height(struct tnode *);
void left_right_rotate(struct tnode **parent);
void left_rotate(struct tnode **parent);
void right_left_rotate(struct tnode **parent);
void right_rotate(struct tnode **parent);
void Balance(struct tnode **t,int V);

void balance_my_tree(struct tnode **root, int data);
int get_bf(struct tnode *t);
struct tnode * delete_main(struct tnode **root, int data);
int height(struct tnode *t);
int count(struct tnode *t);
struct tnode *tdelete(struct tnode *t, int key);

int rsearch(struct tnode *t, int key);

int main()
{
  struct tnode *root;
  int ch,num,k,n,h,c;
   root=NULL;
printf("AVL Trees.\n");
printf("Enter corresponding number to do the operations on AVL Trees.\n");
 while(1)
 {
      printf("\n1.Insert_AVL_trees");
      printf("\n2.Delete_AVL_trees");
      printf("\n3.search");
      printf("\n4.Preorder");
      printf("\n5.inorder");
      printf("\n6.postorder");
      printf("\n7.height");
      printf("\n8.count");
      printf("\n9.exit\n");
      scanf("%d",&ch);
       switch(ch)
       {
         case 1 :printf("Enter the element: ");
                 scanf("%d",&num);
                 Insert(&root,num);
                 break;

         case 2:
                printf("Enter the element: ");
                scanf("%d",&num);
                delete_main(&root,num);
                break;
         case 3:
                printf("Enter the element: ");
                scanf("%d",&num);
                rsearch(root,num);
        case 4:
                preorder(root);
                break;

         case 5:
                inorder(root);
                break;
         case 6:
                postorder(root);
                break;
         case 7:
                h = height(root);
                printf("Height: %d",h);
                break;
         case 8:
                c = count(root);
                printf("Number of nodes: %d",c);
                break;

         case 9:exit(0);

         default: exit(0);
       }
    }
return 0;
  }

void preorder(struct tnode *t)
  {
     if(t!=NULL)
     {
       printf("%d ",t->data);
       preorder(t->left);
       preorder(t->right);
     }
  }
  int height(struct tnode *t)
  {
    int left,right;
    if(t==NULL)
      return -1;
    if((t->left==NULL)&&(t->right==NULL))
     return 0;
    left=height(t->left);
    right=height(t->right);
    if(left>right)
      return(left+1);
    return(right+1);
  }

 void Insert(struct tnode **t,int key)
 {
   struct tnode *curr, *prev, *temp;

    temp=(struct tnode*)malloc(sizeof(struct tnode));
    temp->data=key;
    temp->left=temp->right=NULL;

    if(*t==NULL)//if empty tree
       *t=temp;//copy the temp into root
    else
     {
       prev=NULL;
       curr=*t;
       while(curr!=NULL)
       {
         prev=curr;
         if(key<curr->data)
             curr=curr->left;
        else
           curr=curr->right;
       }
    if(key<prev->data)
      prev->left=temp;
    else
      prev->right=temp;
    Balance(t,key);
    preorder(*t);
   }
 }

 void postorder(struct tnode *t)

  {

     if(t!=NULL)

     {

       postorder(t->left);

       postorder(t->right);

       printf("%d ",t->data);

     }

  }



  void inorder(struct tnode *t)

  {

     if(t!=NULL)

     {

       inorder(t->left);

       printf("%d ",t->data);

       inorder(t->right);

     }

  }

 int count(struct tnode *t)

  {

    int a,b;

    if(t==NULL)

     return 0;

    a=count(t->left);

    b=count(t->right);

    return(a+b+1);

  }

struct tnode *tdelete(struct tnode *t, int key)

  {

    struct tnode *curr, *temp, *prev, *p, *q;

    curr=t;

    //search for key

    prev=NULL;

    while((curr!=NULL)&&(curr->data!=key))

    {

       prev=curr;

       if(key<curr->data)

          curr=curr->left;

       else

          curr=curr->right;

    }

   if(curr==NULL)//key not found

   {

     printf("Node not found..\n");

      return t;

   }



   //if one subtree or no subtrees present

   if((curr->left==NULL)||(curr->right==NULL))

   {

     if(curr->left==NULL)

       q=curr->right;//get the non empty subtree, (right)

     else

       q=curr->left;//get the left subtree



    if(prev==NULL)//deleting root with one subtree

      {

      free(curr);

      return q;

      }

    if(curr==prev->left)

      prev->left=q;

    else

      prev->right=q;

    free(curr);

  }

  else

  {

    //both the subtrees present

    //find the inorder successor,

    //keep track of the prarent of inorder successor

    p=curr;//for the parent of inorder successor

    temp=curr->right;

    while(temp->left!=NULL)

     {

       p=temp;

       temp=temp->left;

     }

    //inorder successor found(temp)

    if(p!=curr)

      p->left=temp->right;

    else

      curr->right=temp->right;

    curr->data=temp->data;//replace the data of node to be deleted

    free(temp);           //with data of inorder succesor

   }

  return t;

}
//----------------------AVL TREES INSERTION -----------------------------------

void Balance(struct tnode **t,int key)
{
    if((*t)!=NULL)
    {
        Balance(&((*t)->left),key);
        Balance(&((*t)->right),key);
        int bf = get_bf(*t);
        printf("%d\n",bf);
        if(abs(bf)>1)
        {
            printf("yes\n");
            int G= (*t)->data;
            printf("G=%d\n",G);
            int left=0,right=0;

            if(key < G)
            {
                int S = (*t)->left->data;
                printf("S=%d\n",S);
                if(key>S)
                {
                    printf("LR rotation\n");
                    left_right_rotate(&(*t));
                }
                if(key<S)
                {
                    printf("R rotation\n");
                    right_rotate(&(*t));
                }
            }

            else if(key > G)
            {
                int P = (*t)->right->data;
                printf("P=%d\n",P);
                if(key>P)
                {
                    printf("L rotation\n");
                    left_rotate(&(*t));

                }
                if(key<P){
                        printf("RL rotation\n");
                    right_left_rotate(&(*t));
                }
            }
            else
            {

                return;
            }
        }

    }
}

void right_rotate(struct tnode **parent)
{
	if(*parent != NULL && ((*parent)->left!=NULL))
	{
		struct tnode *t = *parent;
		struct tnode *temp = t->left->right;
		(*parent) = t->left;
		t->left = temp;
		(*parent)->right = t;
	}
}

void left_right_rotate(struct tnode **parent)
{
    if(*parent !=NULL && (*parent)->left != NULL)
    {
        struct tnode *temp1 = (*parent)->left;
        struct tnode *temp2 = temp1->right;
        (*parent)->left = temp2;
        temp1->right = temp2->left;
        temp2->left = temp1;
        right_rotate(parent);
    }
}

void left_rotate(struct tnode **parent)
{
    if(*parent != NULL && ((*parent)->right != NULL))
    {
        struct tnode *temp1 = *parent;
        struct tnode *temp2 = (*parent)->right->left;
        *parent = temp1->right;
        (*parent)->left = temp1;
        temp1->right = temp2;
    }
}

void right_left_rotate(struct tnode **parent)
{
    if(*parent !=NULL && (*parent)->right != NULL)
    {
        struct tnode *temp1 = (*parent)->right;
        struct tnode *temp2 = temp1->left;
        (*parent)->right = temp2;
        temp1->left = temp2->right;
        temp2->right = temp1;
        left_rotate(parent);
    }
}

//--------------------AVL TREES DELETION------------------------------

struct tnode * delete_main(struct tnode **root, int data)
{

    *root = tdelete(*root, data);

    preorder(*root);

    balance_my_tree(root, data);

    return *root;

}



void balance_my_tree(struct tnode **root, int data)

{

    int bf;

    int bf_right;

    int bf_left;

    if(count(*root) < 3 )

        return;

    else{

        balance_my_tree(&((*root)->left), data);

        balance_my_tree(&((*root)->right), data);

        bf = get_bf(*root);

        if(abs(bf) > 1){

            struct tnode *critical_node = *root;

            if(critical_node->data < data){

                    bf_left = get_bf(critical_node->left);

                if((bf_left == 0) || (bf_left == 1)){
                    printf("right_rotate\n");

                    right_rotate(root);

                }else{
                    printf("left_right_rotate\n");
                    left_right_rotate(root);

                }

            }else{

                bf_right = get_bf(critical_node->right);

                if((bf_right==0) || (bf_right==-1)){
                    printf("left_rotate\n");
                    left_rotate(root);

                }

                else{
                    printf("right_left_rotate\n");
                    right_left_rotate(root);

                }

            }

        }

    }

}



int get_bf(struct tnode *t)

{

    return height(t->left) - height(t->right);

}

//-------------------AVL TREES SEARCHING---------------------------


  int rsearch(struct tnode *t, int key)

  {

     int l;

    if(t==NULL)

      return 0;

    if(t->data==key)

      return 1;

    if(key<t->data)

      l=rsearch(t->left,key);//search key in the left subtree

    else

      l=rsearch(t->right,key);//search key in the right subtree

    return l;

   }
