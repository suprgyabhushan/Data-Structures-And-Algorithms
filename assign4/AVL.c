#include<stdio.h>
#include<stdlib.h>
#include<math.h>

struct tree
{
    struct tree *parent;
    long long int val;
    struct tree *lc;
    struct tree *rc;
};

void zig(struct tree *,struct tree **);

int height(struct tree *n)
{
    height2(n,-1);
}

int height2(struct tree *n,int h)
{
    if(n==0)
        return h;

    struct tree *tmp1=n->lc;
    struct tree *tmp2=n->rc;
    h+=1;
    int h1=height2(tmp1,h);
    int h2=height2(tmp2,h);
    if(h1>h2)
        return h1;
    else
        return h2;
}

struct tree * insert(struct tree *st,long long int x)
{
    struct tree *tmp;
    if(st->val>=x)
    {
        tmp=st->lc;
        if(tmp==0)
        {
            struct tree *new=(struct tree *)malloc(sizeof(struct tree));
            st->lc=new;
            new->val=x;
            new->lc=0;
            new->rc=0;
            new->parent=st;
            return new->parent->parent;
        }
    }
    else
    {
        tmp=st->rc;
        if(tmp==0)
        {
            struct tree *new=(struct tree *)malloc(sizeof(struct tree));
            st->rc=new;
            new->val=x;
            new->lc=0;
            new->rc=0;
            new->parent=st;
            return new->parent->parent;
        }
    }

    insert(tmp,x);
}

int search(struct tree *st,long long int x)
{
    if(st==0)
        return 0;

    if(x>st->val)
        st=st->rc;
    else if(x<st->val)
        st=st->lc;
    else 
        return 1;

    search(st,x);
}

struct tree *delete(struct tree *st,long long int x)
{
    if(st==0)
        return 0;

    if(x>st->val)
        st=st->rc;
    else if(x<st->val)
        st=st->lc;
    else 
    {
        struct tree *l=st->lc;
        struct tree *r=st->rc;
        if(l==0)
        {
            if(st->rc!=0)
                st->rc->parent=st->parent;
            if(st->parent!=0)
                {
                if(st->parent->lc==st)
                    st->parent->lc=st->rc;
                else
                    st->parent->rc=st->rc;
                }
            else
                *(&st)=st->rc;
        }
        else if(r==0)
        {
            st->lc->parent=st->parent;
            if(st->parent!=0)
                {
                if(st->parent->lc==st)
                    st->parent->lc=st->lc;
                else
                    st->parent->rc=st->lc;
                }
            else
                *(&st)=st->lc;
        }
        else
        {
            struct tree *ptr=st->lc;
            while(1)
            {
                if(ptr->rc==0)
                    break;
                ptr=ptr->rc;
            }
            st->val=ptr->val;
            st=ptr->parent;
            if(ptr->parent->rc==ptr)
                ptr->parent->rc=0;
            else
                ptr->parent->lc=0;
        }
        return st->parent;
    }
    delete(st,x);
}

void zigzag(struct tree *z,int d,struct tree **st)
{
    struct tree *x,*y;
    if(d==1)
    {
        y=z->rc;
        x=y->lc;
        z->rc=x->lc;
        if(x->lc!=0)
            x->lc->parent=z;
        y->lc=x->rc;
        if(x->rc!=0)
            x->rc->parent=y;
        x->lc=z;
        x->rc=y;
    }
    else
    {
        y=z->lc;
        x=y->rc;
        z->lc=x->rc;
        if(x->rc!=0)
            x->rc->parent=z;
        y->rc=x->lc;
        if(x->lc!=0)
            x->lc->parent=y;
        x->rc=z;
        x->lc=y;
    }
    struct tree *p=z->parent;
    z->parent=x;
    y->parent=x;
    x->parent=p;
    if(p!=0)
        {
        if(p->lc==z)
            p->lc=x;
        else
            p->rc=x;
        }
    else
        *st=x;
    zig(p,st);
}

void zigzig(struct tree *z,int d,struct tree **st)
{
    struct tree *x,*y;
    if(d==1)
    {
        y=z->rc;
        x=y->rc;
        z->rc=y->lc;
        if(y->lc!=0)
        y->lc->parent=z;
        y->lc=z;
        y->rc=x;
    }
    else
    {
        y=z->lc;
        x=y->lc;
        z->lc=y->rc;
        if(y->rc!=0)
        y->rc->parent=z;
        y->rc=z;
        y->lc=x;
    }
    struct tree *p=z->parent;
    z->parent=y;
    x->parent=y;
    y->parent=p;
    if(p!=0)
    {
        if(p->lc==z)
            p->lc=y;
        else
            p->rc=y;
    }
    else
        *st=y;
    zig(p,st);
}

void zig(struct tree *check,struct tree **st)
{
    if(check==0)
        return;
    int hl=height(check->lc);
    int hr=height(check->rc);
    if(abs(hl-hr)>1)
    {
        if(hl<hr)
        {
            if(height(check->rc->lc)>height(check->rc->rc))
                zigzag(check,1,st);
            else
                zigzig(check,1,st);
        }
        else
        {
            if(height(check->lc->rc)>height(check->lc->lc))
                zigzag(check,0,st);
            else
                zigzig(check,0,st);
        }
    }
    else
        zig(check->parent,st);
}

int main(int argc,char *argv[])
{
    FILE *in=fopen(argv[1],"r");
    //FILE *in=fopen("input","r");
    int n;
    fscanf(in,"%d\n",&n);
    int i;
    struct tree *st=0;
    int count=0;
    for(i=0;i<n;i++)
    {
        int option;
        long long int x;
        fscanf(in,"%d %lld\n",&option,&x);
        if(option==1)
        {
        count++;
            //insert element
            if(st==0)
            {
                st=malloc(sizeof(struct tree));
                st->parent=0;
                st->val=x;
                st->lc=0;
                st->rc=0;
                //printf("inserted\n");
            }
            else
            {
                struct tree *check=insert(st,x);
                //printf("inserted\n");
                zig(check,&st);
            }
        }
        if(option==0)
        {
            int ans=search(st,x);
            if(ans==0)
                printf("not found\n");
            else
                printf("found\n");
        }
        if(option==2)
        {
            struct tree *check=delete(st,x);
            if(check==0)
            {    
                //printf("element not present\n");
            }
            else
            {
                //printf("deleted\n");
                zig(check,&st);
            }
        }
//    printf("height of root: %d, should be %f\n",height(st),log2(count));
  //  printf("height of lc: %d, height of rc: %d\n",height(st->lc),height(st->rc));
    }
}
