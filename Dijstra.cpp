#include<iostream>
using namespace std;

class grafo{
public:
    class Arista;
    int nombre;
    bool visited=false;
    grafo* sgte;
    Arista* ady;
    grafo* cabeza;
    int acumulado;
    grafo(){
        sgte = cabeza = NULL;
        ady = NULL;
    }
    void insertarVertice(int);
    void mostrarGrafo();
    void insertarArista(int, int, int);
    grafo * buscarVertice(int);
    grafo::Arista * minArista(int);
    grafo::Arista * buscaArista(int, int);
    int cantVertices();
    void Dijkstra(int);
};
class grafo::Arista{
public:
    grafo* destino;
    Arista* sgte;
    int peso;
    bool min = false;
    Arista(){
        destino = NULL;
        sgte = NULL;
    }
};
void grafo::insertarVertice(int nom) {
    grafo* nuevo=new grafo();
    grafo* ind;
    nuevo->nombre=nom;
    if (cabeza==NULL){
        cabeza=nuevo;
        return;
    }
    ind=cabeza;
    while(ind->sgte!=NULL){
        ind=ind->sgte;
    }
    ind->sgte=nuevo;
    ind->cabeza=this->cabeza;
}

void grafo::mostrarGrafo(){
    grafo* ind=cabeza;
    while(ind!=NULL){
        cout<<ind->nombre<<"\t|  ";
        Arista* inda;
        inda=ind->ady;
        while(inda!=NULL){
            cout<<"("<<inda->peso<<") "<<inda->destino->nombre<<"   ";
            inda=inda->sgte;
        }
        cout<<endl;
        ind=ind->sgte;
    }
}

void grafo::insertarArista(int ini, int fin, int peso){
    grafo* indi;
    grafo* indf;
    indi=cabeza;
    while (indi!=NULL){
        if (indi->nombre==ini)
            break;
        indi=indi->sgte;
    }
    if (indi==NULL){
        return;
    }
    indf=cabeza;
    while (indf!=NULL){
        if (indf->nombre==fin)
            break;
        indf=indf->sgte;
    }
    if (indf==NULL){
        return;
    }
    Arista* nuevo=new Arista();
    nuevo->peso=peso;
    if (indi->ady==NULL){
        indi->ady=nuevo;
        nuevo->destino=indf;
        return;
    }
    Arista* inda;
    inda=indi->ady;
    while(inda->sgte!=NULL){
        inda=inda->sgte;
    }
    inda->sgte=nuevo;
    nuevo->destino=indf;
}

grafo * grafo::buscarVertice(int v){
    grafo *ind=cabeza;
    while(ind!=NULL){
        if(ind->nombre==v){
            return ind;
        }
        ind=ind->sgte;
    }
    return NULL;
}

grafo::Arista * grafo::buscaArista(int u, int v){
    grafo *ind = buscarVertice(u);
    Arista *inda=ind->ady;
    while (inda!=NULL){
        if(inda->destino->nombre==v){
            return inda;
        }
        inda=inda->sgte;
    }
    return NULL;
}

grafo::Arista * grafo::minArista(int v){
    grafo *indV= buscarVertice(v);
    int minpeso;
    Arista *minA=new Arista(), *indMin;
    indMin=indV->ady;
    minpeso=999;
    while(indMin!=NULL){
        if(indMin->peso<minpeso && !indMin->min && !indMin->destino->visited){
            minA=indMin;
            minpeso=indMin->peso;
        }
        indMin=indMin->sgte;
    }
    return minA;
}

int grafo::cantVertices(){
    int cont=0;
    grafo *ind=cabeza;
    while(ind!=NULL){
        cont++;
        ind=ind->sgte;
    }
    return cont;
}

void grafo::Dijkstra(int v){
    grafo *spt = new grafo();
    grafo *ind = cabeza;
    grafo * inicio = buscarVertice(v);
    spt->insertarVertice(inicio->nombre);
    inicio->visited=true;
    grafo *indT, *minVer;
    int cant = cantVertices();
    int *arrSPT = new int[cant];
    arrSPT[0] = cabeza->nombre;
    int i=0;
    int minAcumulado;
    Arista *min, *minCam;
    while (i<cant-1){
        indT=spt->cabeza;
        minAcumulado=999;
        while(indT!=NULL){
            min = minArista(indT->nombre);
            if(min->destino!=NULL){
                min->destino->acumulado = buscarVertice(indT->nombre)->acumulado + min->peso;
                if(min->destino->acumulado<minAcumulado){
                    minAcumulado= min->destino->acumulado;
                    minCam= min;
                    minVer = indT;
                }
            }
            indT=indT->sgte;
        }
        minCam->destino->acumulado=minAcumulado;
        buscaArista(minCam->destino->nombre, minVer->nombre)->min=true;
        buscaArista(minVer->nombre, minCam->destino->nombre)->min=true;
        spt->insertarVertice(minCam->destino->nombre);
        spt->insertarArista(minCam->destino->nombre, minVer->nombre, minCam->peso);
        spt->insertarArista(minVer->nombre, minCam->destino->nombre, minCam->peso);
        minCam->destino->visited=true;
        i++;
        arrSPT[i]=minCam->destino->nombre;
    }
    spt->mostrarGrafo();
    cout<<"T: ";
    for (int j = 0; j < cant; j++) {
        cout<<arrSPT[j]<<" ";
    }
}

void insertarAristas(grafo *g, int v, int u, int peso){
    g->insertarArista(v,u,peso);
    g->insertarArista(u,v,peso);
}

int main() {

    grafo *p = new grafo();
    p->insertarVertice(0);
    p->insertarVertice(1);
    p->insertarVertice(2);
    p->insertarVertice(3);
    p->insertarVertice(4);
    p->insertarVertice(5);
    p->insertarVertice(6);
    p->insertarVertice(7);
    p->insertarVertice(8);
    insertarAristas(p,0,1,4);
    insertarAristas(p,1,2,8);
    insertarAristas(p,0,7,8);
    insertarAristas(p,1,7,11);
    insertarAristas(p,8,7,7);
    insertarAristas(p,6,7,1);
    insertarAristas(p,2,8,2);
    insertarAristas(p,6,8,6);
    insertarAristas(p,2,5,4);
    insertarAristas(p,6,5,2);
    insertarAristas(p,4,5,10);
    insertarAristas(p,4,3,9);
    insertarAristas(p,5,3,14);
    insertarAristas(p,2,3,7);
    insertarAristas(p,2,5,4);
    cout << "Vert\t|  Lista de adyacencia\n";
    p->mostrarGrafo();
    cout<<"-------------------"<<endl;
    int v=0;
    cout<<"Algoritmo de Dijkstra iniciando en el vertice '"<<v<<"':\n";
    cout << "Vert\t|  Lista de adyacencia\n";
    p->Dijkstra(v);
    
    return 0;
}