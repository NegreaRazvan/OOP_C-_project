#include "Tests.h"
#include <cassert>

void Tests::test_create_object(){
    Carte c1 = Carte("Hehe", "Aurel", "SF", 2004);
    assert(c1.getTitlu() == "Hehe");
    assert(c1.getGen() == "SF");
    assert(c1.getAutor() == "Aurel");
    assert(c1.getAnul() == 2004);
    c1.setAnul(2003);
    assert(c1.getAnul() == 2003);
    c1.setAutor("Bob");
    assert(c1.getAutor()=="Bob");
    c1.setGen("BlaBla");
    assert(c1.getGen() == "BlaBla");
    c1.setTitlu("Ciresarii");
    assert(c1.getTitlu()=="Ciresarii");
}

void Tests::test_validate_object(){
    try{
        Carte c1 = Carte("", "", "", -2);
        assert(false);
    } catch (Exception &e){
        assert(string(e.what()) =="An invalid!\nAutor invalid!\nGen invalid!\nTitlu invalid!\n");
    }

}

void Tests::test_add_element() {
    Repository repo = Repository();
    assert(repo.get_carti().empty());
    repo.add_carte(Carte("das","fsa","gvba",2003));
    repo.add_carte(Carte("das","fsa","gvba",2013));
    repo.add_carte(Carte("das","fsa","gvba",2016));
    repo.add_carte(Carte("das","fsa","gvba",1902));
    assert(repo.get_carti().size()==4);
    assert(repo.get_carte(1).getAnul()==2013);
    assert(repo.get_carte(3).getAnul()==1902);

}

void Tests::test_delete_element() {
    Repository repo = Repository();
    repo.add_carte(Carte("das","fsa","gvba",2003));
    repo.add_carte(Carte("das","fsa","gvba",2013));
    repo.add_carte(Carte("das","fsa","gvba",2016));
    repo.add_carte(Carte("das","fsa","gvba",1902));
    assert(repo.get_carti().size()==4);
    repo.delete_carte(1);
    assert(repo.get_carti().size()==3);
    assert(repo.get_carte(1).getAnul()==2016);
    repo.delete_carte(0);
    repo.delete_carte(1);
    repo.delete_carte(0);
    assert(repo.get_carti().empty());
}

void Tests::test_modify_element() {
    Repository repo = Repository();
    repo.add_carte(Carte("das","fsa","gvba",2003));
    repo.add_carte(Carte("das","fsa","gvba",2013));
    repo.modify_carte(Carte("fa","ds","hehe",2000), 1);
    assert(repo.get_carte(1).getAnul()==2000);
    assert(repo.get_carte(1).getTitlu()=="fa");
    assert(repo.get_carte(1).getAutor()=="ds");
    assert(repo.get_carte(1).getGen()=="hehe");
}

void Tests::test_search_element() {
    Repository repo = Repository();
    repo.add_carte(Carte("sad","fsa","gvba",2003));
    repo.add_carte(Carte("fdas","fsa","gvba",2013));
    repo.add_carte(Carte("das","fsa","gvba",2016));
    repo.add_carte(Carte("bdsa","fsa","gvba",1902));
    Carte c1 = repo.get_carte(2);
    assert(repo.search(c1.getTitlu())==2);
    assert(repo.search("aha")==-1);

}

void Tests::test_copy_list() {
    Repository repo = Repository();
    repo.add_carte(Carte("sad","fsa","gvba",2003));
    repo.add_carte(Carte("fdas","fsa","gvba",2013));
    repo.add_carte(Carte("das","fsa","gvba",2016));
    repo.add_carte(Carte("bdsa","fsa","gvba",1902));
    auto elems_cop = repo.copy_list();
    for(int i = 0; i < elems_cop.size(); i++)
        assert(elems_cop.at(i) == repo.get_carte(i));
}

void Tests::test_service_add_element() {
    Service serv = Service();
    try{
        serv.service_get_carti();
        assert(false);
    }
    catch (Exception &e){
        assert(string(e.what())=="Lista goala!\n");
    }
    serv.service_add_carte("das","fsa","gvba",2003);
    serv.service_add_carte("fa","fsa","gvba",2013);
    serv.service_add_carte("bda","fsa","gvba",2016);
    serv.service_add_carte("bhnerws","fsa","gvba",1902);
    assert(serv.service_get_carti().size()==4);
    assert(serv.service_search("fa").getAnul()==2013);
    assert(serv.service_search("bhnerws").getAnul()==1902);
    try{
        serv.service_add_carte("das","fsa","gvba",2003);
        assert(false);
    }
    catch (Exception &e){
        assert(string(e.what())=="Cartea deja apare in lista!\n");
    }
}

void Tests::test_get_all_elements() {
    Service serv = Service();
    serv.service_add_carte("das","fsa","gvba",2003);
    serv.service_add_carte("fa","fsa","gvba",2013);
    serv.service_add_carte("bda","fsa","gvba",2016);
    serv.service_add_carte("bhnerws","fsa","gvba",1902);
    vector<Carte> v = serv.service_get_carti();
    assert(v.size()==4);
//    auto it = v.begin();
//    int s{0};
//    while (it.valid()){
//        s+=it.element().getAnul();
//        it.next();
//    }
//    assert(s==7934);
    serv.service_add_carte("b","a","c",1230);
    v =  serv.service_get_carti();
    assert(v.size()==5);
}

void Tests::test_service_delete_element() {
    Service serv = Service();
    serv.service_add_carte("das","fsa","gvba",2003);
    serv.service_add_carte("fa","fsa","gvba",2013);
    serv.service_add_carte("bda","fsa","gvba",2016);
    serv.service_add_carte("bhnerws","fsa","gvba",1902);
    assert(serv.service_get_carti().size()==4);
    serv.service_delete_carte("fa");
    assert(serv.service_get_carti().size()==3);
    try{
        serv.service_delete_carte("f");
        assert(false);
    }
    catch (Exception &e){
        assert(string(e.what())=="Cartea nu se afla in lista!\n");
    }
}

void Tests::test_service_modify_element() {
    Service serv = Service();
    serv.service_add_carte("das","fsa","gvba",2003);
    serv.service_add_carte("fa","fsa","gvba",2013);
    serv.service_add_carte("bda","fsa","gvba",2016);
    serv.service_add_carte("bhnerws","fsa","gvba",1902);
    assert(serv.service_get_carti().size()==4);
    serv.service_modify_carte("bda", "a","b",2);
    assert(serv.service_search("bda").getAnul()==2);
    assert(serv.service_search("bda").getAutor()=="a");
    assert(serv.service_search("bda").getGen()=="b");
    try{
        serv.service_modify_carte("f","a","b",2);
        assert(false);
    }
    catch (Exception &e){
        assert(string(e.what())=="Cartea nu se afla in lista!\n");
    }
}

void Tests::test_service_search_element() {
    Service serv = Service();
    serv.service_add_carte("das","fsa","gvba",2003);
    serv.service_add_carte("fa","fsa","gvba",2013);
    try{
        serv.service_search("f");
        assert(false);
    }
    catch (Exception &e){
        assert(string(e.what())=="Cartea nu se afla in lista!\n");
    }
}

void Tests::test_filter_element() {
    Service serv = Service();
    serv.service_add_carte("fa","fsa","gvba",2003);
    serv.service_add_carte("fa","fsa","gvba",2016);
    serv.service_add_carte("bda","fsa","gvba",2016);
    serv.service_add_carte("fa","fsa","gvba",1902);
    vector<Carte> v_cop;
    v_cop = serv.service_filter(2016);
    assert(v_cop.size()==2);
    vector<Carte> v_cop_2;
    v_cop_2 = serv.service_filter("fa");
    assert(v_cop_2.size()==3);
}

void Tests::test_sort_element() {
    Service serv = Service();

    serv.service_add_carte("das","fs","gvba",2003);
    serv.service_add_carte("fa","g","fvba",1900);
    serv.service_add_carte("bda","a","gvba",1900);
    serv.service_add_carte("bhnerws","z","gvba",1902);
    vector<Carte> v_copie;
    v_copie=serv.sort_lambda(1,true);
    assert(v_copie.at(0).getAnul()==1900);
    v_copie = serv.sort_lambda(2,false);
    assert(v_copie.at(0).getAnul()==1902);
    v_copie = serv.sort_lambda(3,true);
    assert(v_copie.at(0).getTitlu()=="fa");
}

void Tests::test_Vector() {
    int a{2},b{3},c{5},d{7};
    Vector<int> v;
    v.push_back(a);
    v.push_back(b);
    assert(v.empty()== false);
    assert(v.size()== 2);
    v.erase(0);
    assert(v.size()==1);
    assert(v.at(0)==b);
    v.push_back(c);
    v.push_back(d);
    int i =0;
    for(const auto& el: v) {
        assert(el == v[i]);
        i++;
    }
    try{
        v.erase(-1);
        assert(false);
    }
    catch(std::out_of_range &e) {
        assert(string(e.what())=="Index out of range");
    }
}

void Tests::test_add_cos() {
    string path = "Teste/File_For_Tests";
    Cos cos ;
    assert(cos.get_all_carti().empty());
    cos.add_carte_to_cos(Carte("das","fsa","hnba",2003));
    cos.add_carte_to_cos(Carte("fvca","bvaw","hsa",2013));
    cos.add_carte_to_cos(Carte("gab","fea","gvaw",2016));
    cos.add_carte_to_cos(Carte("bvawf","abgs","waf",1902));
    assert(cos.get_all_carti().size()==4);
    cos.empty_cos();
    assert(cos.get_all_carti().empty());

}

void Tests::test_export_cos() {
    string path = "File_Tests";
    Cos cos;
    cos.add_carte_to_cos(Carte("das","fsa","hnba",2003));
    cos.add_carte_to_cos(Carte("fvca","bvaw","hsa",2013));
    cos.add_carte_to_cos(Carte("gab","fea","gvaw",2016));
    cos.add_carte_to_cos(Carte("bvawf","abgs","waf",1902));
    cos.export_carti(path);
}


void Tests::test_delete_cos() {
    Cos cos ;
    assert(cos.get_all_carti().empty());
    cos.add_carte_to_cos(Carte("das","fsa","hnba",2003));
    cos.add_carte_to_cos(Carte("fvca","bvaw","hsa",2013));
    cos.add_carte_to_cos(Carte("gab","fea","gvaw",2016));
    cos.add_carte_to_cos(Carte("bvawf","abgs","waf",1902));
    cos.delete_carte(3);
    cos.delete_carte(2);
    assert(cos.get_all_carti().size()==2);
}

void Tests::test_modify_cos() {
    Cos cos ;
    assert(cos.get_all_carti().empty());
    cos.add_carte_to_cos(Carte("das","fsa","hnba",2003));
    cos.modify_carte(Carte("das","f","a",3), 0);
    assert(cos.get_all_carti().at(0).getAnul()==3);
}

void Tests::test_service_add_cos() {
    Service serv = Service();
    serv.service_add_carte("das","fsa","gvba",2003);
    serv.service_add_carte("fa","fsa","gvba",2013);
    serv.service_add_carte("bda","fsa","gvba",2016);
    serv.service_add_carte("bhnerws","fsa","gvba",1902);
    serv.service_add_carte_cos("das");
    serv.service_add_carte_cos("fa");
    serv.service_add_carte_cos("bda");
    try {
        serv.service_add_carte_cos("das");
        assert(false);
    }
    catch (Exception &e){
        assert(true);
    }
    assert(serv.service_get_carti_cos().size()==3);
    serv.service_export_cos("testut");
    serv.service_empty_cos();
    try {
        serv.service_get_carti_cos();
    }
    catch (Exception &e){
        assert(string(e.what())=="Lista goala!\n");
    }
    try {
        serv.service_empty_cos();
        assert(false);
    }
    catch (Exception &e){
        assert(true);
    }
    try {
        serv.service_export_cos("testut");
        assert(false);
    }
    catch (Exception &e){
        assert(true);
    }
}

void Tests::test_service_delete_cos() {
    Service serv = Service();
    serv.service_add_carte("das","fsa","gvba",2003);
    serv.service_add_carte("fa","fsa","gvba",2013);
    serv.service_add_carte("bda","fsa","gvba",2016);
    serv.service_add_carte("bhnerws","fsa","gvba",1902);
    serv.service_add_carte_cos("das");
    serv.service_add_carte_cos("fa");
    serv.service_delete_carte("das");
    assert(serv.service_get_carti_cos().size()==1);
}

void Tests::test_service_modify_cos() {
    Service serv = Service();
    serv.service_add_carte("das","fsa","gvba",2003);
    serv.service_add_carte("fa","fsa","gvba",2013);
    serv.service_add_carte("bda","fsa","gvba",2016);
    serv.service_add_carte("bhnerws","fsa","gvba",1902);
    serv.service_add_carte_cos("das");
    serv.service_add_carte_cos("fa");
    serv.service_modify_carte("das","f","a",3);
    assert(serv.service_get_carti_cos().at(0).getAnul()==3);
}

void Tests::test_generate_cos() {
    Service serv = Service();
    serv.service_add_carte("das","fsa","gvba",2003);
    serv.service_add_carte("fa","fsa","gvba",2013);
    serv.service_add_carte("bda","fsa","gvba",2016);
    serv.service_add_carte("bhnerws","fsa","gvba",1902);
    serv.generate_books(3);
    try{
        serv.generate_books(5);
        assert(false);
    }catch (Exception &e){
        assert(true);
    }
}

void Tests::run(){
    test_create_object();
    test_validate_object();

    test_add_element();
    test_delete_element();
    test_modify_element();
    test_search_element();
    test_copy_list();

    test_service_add_element();
    test_get_all_elements();
    test_service_delete_element();
    test_service_modify_element();
    test_service_search_element();
    test_filter_element();
    test_sort_element();

    test_Vector();

    test_add_cos();
    test_export_cos();
    test_delete_cos();
    test_modify_cos();

    test_service_add_cos();
    test_service_delete_cos();
    test_service_modify_cos();
    test_generate_cos();

}














