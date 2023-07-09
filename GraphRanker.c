#include <stdio.h>
#include <stdlib.h>

#define INFINITO 2147483647

typedef struct nodo{
    int index;
    int somma;
    int **m;
    struct nodo*next;
    struct nodo*prev;
}nodo_t;
typedef nodo_t* ptrnodo;

ptrnodo alloca_grafo(ptrnodo node,int n, int counter, FILE *fp){

    char c;
    int i,j;
    node=(ptrnodo)malloc(sizeof(nodo_t));
    node->next=NULL;
    node->prev=NULL;
    node->index=counter;

    node->m=malloc(sizeof(int*)*n);
    c=fgetc(fp);
    for(i=0;i<n;i++){
        node->m[i]=malloc(sizeof(int)*n);
        
        for(j=0;j<n;j++){
            c=fgetc(fp);
            node->m[i][j]=0;
            while((c!=',')&&(c!='\n')){
                node->m[i][j]=(node->m[i][j])*10+c-48;
                c=fgetc(fp);
            }
        }  
    }

    /*for(i=0;i<n;i++){

        for(j=0;j<n;j++)
            printf("%d ",node->m[i][j]);

        printf("\n");
    }*/   

    return node;
    
}

int min_dist(int *dist, int n, int *aux){

    int min=INFINITO;
    int i;
    int index=0;
 
    for(i=1;i<n;i++){
        if(dist[i]<min && dist[i]!=0 && aux[i]!=1){
            min=dist[i];
            index=i;
        }
    }

    return index;

}

void cammini_minimi(ptrnodo grafo, int n){

    int distanza[n];
    int aux[n];
    int c;
    int i,j;
    int somma=0;

    distanza[0]=0;
    aux[0]=1;

    for(i=1;i<n;i++){

        if(grafo->m[0][i]){
            distanza[i]=grafo->m[0][i];
        }
        else{
            distanza[i]=0;
        }
        aux[i]=0;
    }
    
    for(i=0;i<n-1;i++){
        c=min_dist(distanza,n,aux);
        aux[c]=1;
        for(j=0;j<n;j++){
            if((grafo->m[c][j]!=0)&&((distanza[c]+grafo->m[c][j]<distanza[j]) || (distanza[j]==0))){
                distanza[j]=distanza[c]+grafo->m[c][j];
           }    
        }
    }

    for(i=1;i<n;i++){
        if(distanza[i]!=0)
            somma=somma+distanza[i];
    }

    grafo->somma=somma;
    //printf("grafo %d somma %d\n",grafo->index,grafo->somma);

    return;

}

void aggiungi_a_lista(ptrnodo *p, ptrnodo node, int k, int counter){

    ptrnodo tmp;

    if(p[0]==NULL){
            p[0]=node; 
            p[1]=node; 
    }

    else{

        tmp=p[0];
        while(((tmp->next)!=NULL)&&((tmp->somma)<=(node->somma))){
            tmp=tmp->next;
        }

        if((tmp->somma)>(node->somma)){

            if(tmp==p[0]){
                node->next=p[0];
                p[0]->prev=node;
                p[0]=node;          
            }
            
            else{

                node->prev=tmp->prev;
                node->next=tmp;
                node->next->prev=node;
                node->prev->next=node;
                //printf("swap dei puntatori\n");
            }  
        }
        
        else{
 
            node->prev=tmp;
            node->next=NULL;
            tmp->next=node;
            p[1]=node;
        }  
    }

    if(counter>k){
        tmp=p[1];
        p[1]=p[1]->prev;
        p[1]->next=NULL;
        free(tmp);
    }
    
    /*tmp=t;
    printf("la lista attualmente è':\n");
    while(tmp!=NULL){
        printf("%d con somma %d\n",tmp->index, tmp->somma);
        tmp=tmp->next;
    }
    printf("\n");*/
    
    return;
}


void print_topk(ptrnodo t,int k){

    //printf("sono entrato in print_topk con k=%d\n",k);
    ptrnodo tmp=t;
    for(int i=0; i<k && tmp!=NULL;i++){
        printf("%d",tmp->index);
        
        tmp=tmp->next;
        if(i!=(k-1)&&tmp!=NULL)
            printf(" ");
    }
    printf("\n");
    return;
}

int main(){
    int n=0,k=0; 
    char c;
    char s[15];
    int counter=0;
    //FILE *fp=fopen("input_1.txt","r");
    FILE *fp=stdin;
    ptrnodo node=NULL;
    ptrnodo p[2]={NULL, NULL};
   
    c=fgetc(fp);
    while(c!=' '){
        n=n*10+c-48;
        c=fgetc(fp);
    }

    c=fgetc(fp);
    while(c!='\n'){
        k=k*10+c-48;
        c=fgetc(fp);
    }
    //printf("ho letto n=%d, k=%d\n",n,k);
    while(fgets(s,14,fp)!=NULL){

        //printf("ho letto la stringa %s\n",s);
        while(s[0]!='T'){
            //alloco il grafo
            node=alloca_grafo(node,n,counter,fp);

            cammini_minimi(node,n);
            
            for(int i=0;i<n;i++)
                free(node->m[i]);
            free(node->m);

            counter++;

            aggiungi_a_lista(p,node,k,counter);

            if(fgets(s,14,fp)==NULL)
                return 1;
        }
        //printf("sono uscito dal while per Topk\n");
        print_topk(p[0],k);
    }
    //fclose(fp);
    return 0;
}