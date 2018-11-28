#include <iostream>
#include <fstream>
#include <list>
#include <cstdlib>
using namespace std;

class Product{
    int id;
    string name;
    double unitPrice;
    bool stock;
    bool status;
public:
    Product(){
        this->id=0;
        this->name="";
        this->unitPrice=0.0;
        this->stock=0;
        this->status=0;

    }
    void setProduct(int id, string name, double unitPrice, int stock, bool status){
        this->id=id;
        this->name=name;
        this->unitPrice=unitPrice;
        this->stock=stock;
        this->status=status;
    }

    void setId(int id){
        this->id=id;
    }
    void setName(string name){
        this->name=name;
    }

	void setUnitprice(double unitPrice) {
		this->unitPrice = unitPrice;
	}
	void setStock(int stock) {
		this->stock = stock;
	}
	void setStatus(bool status) {
		this->status = status;
	}

    int getID(){
        return this->id;
    }
    string getName(){
        return this->name;
    }
    double getUnitprice(){
        return this->unitPrice;
    }
    int getStock(){
        return this->stock;
    }
    bool getStatus(){
        return this->status;
    }


    bool operator==(Product p){
        if(this->getID()==p.getID()){
            return true;
        }
        else{
            return false;
        }
    }
};

list<Product> productList;

void initializeProductList(){
    int id;
    string name;
    double unitPrice;
    int stock;
    bool status;
    ifstream fin;
    fin.open("Products.txt");
    while(!fin.eof()){
        fin>>id>>name>>unitPrice>>stock>>status;
        Product p;
        p.setProduct(id,name,unitPrice,stock,status);
        productList.push_back(p);
    }
}
Product* searchById(int id){
    list<Product>::iterator i = productList.begin();
	for(i;i != productList.end();i++){
		if(i->getID()==id) return &(*i);
		else return(NULL);
	}
}
void addProduct(Product product){
    productList.push_back(product);
}
void editProduct(Product* product, string name){
    product->setName(name);
}
void deleteProduct(Product product){
    for(list<Product>::iterator j=productList.begin();j!=productList.end();j++)
{
        if(j->getID()==product.getID())
        {
            productList.erase(j);
        }
    }
}
void printProduct(Product product){
    cout<<"ID:      "<<product.getID()<<endl;
    cout<<"Name:    "<<product.getName()<<endl;
    cout<<"Price:   "<<product.getUnitprice()<<endl;
    cout<<"Stock:   "<<product.getStock()<<endl;
    cout<<"Status:  "<<product.getStatus()<<endl;
}
void printAllProducts(){
    for(list<Product>::iterator l=productList.begin();l!=productList.end();l++)
    {
        cout<<l->getID()<<" ";
        cout<<l->getName()<<" ";
        cout<<l->getUnitprice()<<" ";
        cout<<l->getStock()<<" ";
        cout<<l->getStatus()<<endl<<endl;
    }
}
void save()
{
    ofstream fout;
    fout.open("Products.txt");

    for(list<Product>::iterator m=productList.begin();m!=productList.end();m++)
    {
        fout<<m->getID()<<" ";
        fout<<m->getName()<<" ";
        fout<<m->getUnitprice()<<" ";
        fout<<m->getStock()<<" ";
        fout<<m->getStatus()<<endl;
    }
    fout.close();
}

int main(){

    int choice,id;
    string name;
    double unitprice;
    int stock;
    bool status;

    Product p1;

    initializeProductList();
ui:
    cout<<"================================"<<endl;
    cout<<"1. Search Products"<<endl;
    cout<<"2. View All Products"<<endl;
    cout<<"3. Add New Product"<<endl;
    cout<<"4. Edit Product"<<endl;
    cout<<"5. Delete Product"<<endl;
    cout<<"6. Clear Screen"<<endl;
    cout<<"7. Exit"<<endl;
    cout<<"================================="<<endl;
    cout<<"Enter your choice: ";
    cin>>choice;

    switch(choice){
    case 1: cout<<"------------------------------------------"<<endl;
        cout<<"Showing Product Detail--------------------"<<endl;
        cout<<"Enter Product id: ";
        cin>>id;
        Product *p;
        p = searchById(id);
        if(p==0)
            cout<<"Product not found!"<<endl;
        else
            printProduct(*p);
        cout<<"------------------------------------------"<<endl;
        break;
    case 2:
        cout<<"------------------------------------------"<<endl;
        printAllProducts();
        cout<<"------------------------------------------"<<endl;
        break;
    case 3:
        {
            cout<<"------------------------------------------"<<endl;
            cout<<"Adding A product--------------------------"<<endl;

            cout<<"Enter Product ID: ";
            cin>>id;
            cout<<"Enter Product name: ";
            cin>>name;
            cout<<"Enter UnitPrice: ";
            cin>>unitprice;
            cout<<"Enter Product Stock: ";
            cin>>stock;
            cout<<"Enter Product Status"<<" : ";
            cin>>status;
            p1.setId(id);
            p1.setName(name);
            p1.setUnitprice(unitprice);
            p1.setStock(stock);
            p1.setStatus(status);
            addProduct(p1);
        }
        save();
        break;
    case 4:
        {
            cout<<"Enter Product ID: ";
            cin>>id;
            cout<<"Enter Edited Product name: ";
            cin>>name;
            if(searchById(id)==0){
				cout << endl << "Product Not Found!" << endl << endl;
			}
			else{
				editProduct(searchById(id),name);
				cout << endl << "Product Edited!" << endl << endl;
				cout << "================================================" <<endl<<endl;
			}
        }
        save();
        break;
    case 5:
        {
            cout<<"Enter Product ID: ";
            cin>>id;

            p1.setId(id);

            deleteProduct(p1);
        }
        save();
        break;
    case 6:
        system("CLS");
        break;
    case 7:
        exit(0);
        break;
    default:
        exit(1);
    }
    goto ui;

    return 0;
}

