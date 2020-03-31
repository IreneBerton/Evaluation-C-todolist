#include <cstring>
#include <iostream>
#include <fstream>
#include <ctime>

int main(){

    std::string str = "g++ Todolist.cpp -o test";
    const char *command = str.c_str(); 
    system(command); 
    system("./test reset");
    std::cout<<">>>>>>>>>>>>>>>>>>EN FONCTIONNEMENT EN MODE NORMAL"<<'\n'<<std::endl;
    //Je suis consciente que pour le fonctionnement normal, le jeu de test doit être complété par 
    //un controle visuel et qu'il ne répond sans doute pas à vos attentes, mais je n'ai pas trouvé 
    //de manière compacte et non répétitive de le faire avec l'architecture de mon code. La partie
    //fonctionnement anormal correspond je pense mieux à l'esprit d'un véritable test. 
    //EN FONCTIONNEMENT NORMAL CE FICHIER DOIT PERMETTRE :
    //la création d'une tache (tache1)
    std::cout<<'\n'<<">>>>>>>>>>> création des taches :"<<'\n'<<std::endl;
    system("./test create --title tache1");
    //La création d'une tache avec description (tache2, "descr")
    system("./test create --title tache2 --description descr"); 
    //la création d'une tache avec priorite (tache3, "prio")
    system("./test create --title tache3"); 
    //la création d'une tache avec priorite puis description (tache4, "prio2", "descr2")
    system("./test create --title tache4"); 
    //la création d'une tache avec description puis priorite (tache5 "descr3", "prio3")
    system("./test create --title tache5"); 
    std::cout<<'\n'<<">>>>>>>>>>> création des sous taches :"<<'\n'<<std::endl;
    //la création d'une sous tache (id 1, "sstache1")
    system("./test modify --id 1 undertask --title sstache1 "); 
    //La création d'une sous tache avec priorite (id 2, "sstache2", "descr4")
    system("./test modify --id 2 undertask --title sstache2 --description descr4 "); 
    //la création d'une sous tache avec priorite (id 2, "sstache3", "prio4")
    system("./test modify --id 2 undertask --title sstache3 --priority prio4"); 
    //la création d'une sous tache avec priorite puis description (id3, "sstache4", "prio5", "descr5")
    system("./test modify --id 3 undertask --title sstache4 --priority prio5 --description descr5"); 
    //la création d'une sous tache avec description puis priorite (id1, "sstache5", "descr6", "prio6")
    system("./test modify --id 1 undertask --title sstache5 --description descr6 --priority prio6"); 

    //la création d'une sous sous tache (id 6, "sssstache1")
    system("./test modify --id 6 undertask --title sssstache1 "); 
    //la création d'une sous sous tache avec description et priorite (id 7, "sssstache2", "descr7", "prio7")
    system("./test modify --id 7 undertask --title sssstache2 --priority prio7 --description descr7"); 

    //la modification du titre d'une tache (id1, "nouveautitre")
    system("./test modify --id 1 title --nouvtitre "); 
    //la modification de la description d'une tache (id2, "nouvelledescr")
    system("./test modify --id 2 description --nouvelledescr "); 
    //la modification de la priorité d'une tache (id3, "nouvelleprio")
    system("./test modify --id 3 priority --nouvelleprio "); 
    //la modification de la cloture d'une tache possédant des sous taches avec "Fermee" (id 4, "Fermee")
    system("./test modify --id 4 close --Fermee "); 
    //la modification de la cloture d'une tache possédant des sous taches avec "Terminee" (id 5, "Terminee" )
    system("./test modify --id 2 close --Terminee "); 
    //la modification du titre d'une sous tache (id6, "nouveautitre2")
    system("./test modify --id 6 title --nouveautitre2 "); 
    //la modification de la description d'une sous tache (id7, "nouvelledescr2")
    system("./test modify --id 7 description --nouvelledescr2 "); 
    //la modification de la priorité d'une sous tache (id8, "nouvelleprio2")
    system("./test modify --id 8 priority --nouvelleprio2 "); 
    //la modification de la cloture d'une sous tache possédant des sous taches avec "Fermee" (id 6, "Fermee")
    system("./test modify --id 6 close --Fermee"); 
    //la modification de la cloture d'une sous tache possédant des sous taches avec "Terminee" (id 7, "Terminee")
    system("./test modify --id 7 close --Terminee "); 

    //lister toutes les taches
    std::cout<<'\n'<<">>>>>>>>>>> liste de toutes les taches :"<<'\n'<<std::endl;
    system("./test list "); 
    //lister toutes les taches avec une certaine priorité
    std::cout<<'\n'<<">>>>>>>>>>> liste de toutes les taches de priorite nouvelleprio:"<<'\n'<<std::endl;
    system("./test list --priority nouvelleprio"); 
    //lister toutes les taches avec une certaine date de création
    std::cout<<'\n'<<">>>>>>>>>>> liste de toutes les taches creees aujourd hui:"<<'\n'<<std::endl;
    time_t dc = time(0);
    std::string dtoday = (std::string(ctime(&dc))).substr(0,24);
    std:: string date = dtoday.substr(0,10) + " " +dtoday.substr(20, dtoday.size() - 20);
    std::string strcommand = "./test list --dcreation '" + date +"'";
    const char *commanddate = strcommand.c_str(); 
    system(commanddate); 
    //lister toutes les taches avec un certain statut
    std::cout<<'\n'<<">>>>>>>>>>> liste de toutes les taches de statut fermé:"<<'\n'<<std::endl;
    system("./test list --status Fermee"); 
    //lister toutes les taches avec un certain pourcentage
    std::cout<<'\n'<<">>>>>>>>>>> liste de toutes les taches ayant un pourcentage nul:"<<'\n'<<std::endl;
    system("./test list --percent equ0"); 
    //lister toutes les taches avec un pourcentage inférieur ou égal à un certain pourcentage
    std::cout<<'\n'<<">>>>>>>>>>> liste de toutes les taches au pourcentage supérieur ou égal à 50% :"<<'\n'<<std::endl;
    system("./test list --percent sup50"); 
    //lister toutes les taches avec un pourcentage supérieur ou égal à un certain pourcentage
    std::cout<<'\n'<<">>>>>>>>>>> liste de toutes les taches au pourcentage inférieur ou égal à 50% :"<<'\n'<<std::endl;
    system("./test list --percent inf50"); 

    //tester que reset fonctionne;
    std::cout<<'\n'<<">>>>>>>>>>> liste après réinitialisation :"<<'\n'<<std::endl;
    system("./test reset");
    system("./test list");

    std::cout<<'\n'<<'\n'<<"//On constate que pour le fonctionnement normal, on ne plante pas et on a les résultats attendus."<<'\n'<<'\n'<<std::endl;
    std::cout<<'\n'<<'\n'<<">>>>>>>>>>>>>>>>>>EN FONCTIONNEMENT ANORMAL :"<<'\n'<<std::endl;
    system("./test create --title tache1"); 
    std::ofstream output("fichier.txt");  
    std::string ligne;
    std::string commentaire;
    bool booleen = true;
    
    //EN FONCTIONNEMENT ANORMAL CE FICHIER DOIT REPONDRE, QUAND L'UTILISATEUR DECIDE DE :
    //ne pas entrer d'argument : "Entrer une methode"
    system("./test > fichier.txt");
    output.close();
    std::ifstream input("fichier.txt");
    std::getline(input,ligne);
    input.close();
    if (ligne != "Entrer une methode"){

        std::cout<<"Probleme à : Entrer une methode"<<std::endl;
        booleen = false;
    }    
    std::remove("fichier.txt");
    std::ofstream output1("fichier.txt");  
    //entrer une methode inconnue : "Methode inconnue"
    system("./test tutu > fichier.txt");
    output1.close();
    std::ifstream input1("fichier.txt");
    std::getline(input1,ligne);
    input1.close();   
    if (ligne != "Methode inconnue"){
        std::cout<<"Probleme à : Methode inconnue"<<std::endl;
        booleen = false;
    }
    std::ofstream output2("fichier.txt"); 
    //Methode create :
        //Ne pas respecter la racine  create --title : "Entrer le nouveau titre derriere --title"
        system("./test create title titre > fichier.txt");
        output2.close();
    std::ifstream input2("fichier.txt");
    std::getline(input2,ligne,'\n');
    input2.close();
    if (ligne != "Entrer le nouveau titre derriere --title"){
        std::cout<<"Probleme à :Entrer le nouveau titre derriere --title"<<std::endl;
        booleen = false;
    }
    std::ofstream output3("fichier.txt");  
        //Si le cinquième terme de la commande existe : ne pas avoir le cinquième terme sous la forme --description ou --priority : "Format non respecte, cf doc"
        system("./test create --title titre description descr > fichier.txt");
        output3.close();
    std::ifstream input3("fichier.txt");
    std::getline(input3,ligne,'\n');
    input3.close();
    if (ligne != "Format non respecte, cf doc"){
        std::cout<<"Probleme à : Format non respecte, cf doc"<<std::endl;
        booleen = false;
    }
    std::ofstream output4("fichier.txt"); 
                                                         //ne pas avoir de sixième terme : "Entrer un priorite ou un commentaire"
        system("./test create --title titre --description > fichier.txt");
    output4.close();
    std::ifstream input4("fichier.txt");
    std::getline(input4,ligne,'\n');
    input4.close();
    if (ligne != "Entrer un priorite ou un commentaire"){
        std::cout<<"Probleme à : Entrer un priorite ou un commentaire"<<std::endl;
        booleen = false;
    }
    std::ofstream output5("fichier.txt"); 
        //Si le septième terme de la commande exsite : ne pas avoir le septième terme sous la forme --description ou --priority : "Format non respecte, cf doc"
        system("./test create --title titre --description descr priority prior > fichier.txt");
   output5.close();
    std::ifstream input5("fichier.txt");
    std::getline(input5,ligne,'\n');
    input5.close();
    if (ligne != "Format non respecte, cf doc"){
        std::cout<<"Probleme à : Format non respecte, cf doc"<<std::endl;
        booleen = false;
    }
    std::ofstream output6("fichier.txt"); 
                                                         //ne pas avoir de huitième terme : "Entrer un priorite ou un commentaire"
        system("./test create --title titre --description descr --priority > fichier.txt");
    output6.close();
    std::ifstream input6("fichier.txt");
    std::getline(input6,ligne,'\n');
    input6.close();
    if (ligne != "Entrer un priorite ou un commentaire"){
        std::cout<<"Probleme à : Entrer un priorite ou un commentaire"<<std::endl;
        booleen = false;
    }
    std::ofstream output7("fichier.txt"); 
    //Methode modify : 
        //Ne pas avoir au moins 6 termes : "Le format de la methode modify n'est pas respecte."
        system("./test modify --id 1 > fichier.txt");
    output7.close();
    std::ifstream input7("fichier.txt");
    std::getline(input7,ligne,'\n');
    input7.close();
    if (ligne != "Le format de la methode modify n'est pas respecte."){
        std::cout<<"Probleme à : Le format de la methode modify n'est pas respecte."<<std::endl;
        booleen = false;
    }
    std::ofstream output8("fichier.txt"); 
        //Ne pas respecter la racine modify --id : "Entrer l'id de la tache/sous tache a modifier derrière --id"
        system("./test modify id 1 close --Terminee> fichier.txt");
    output8.close();
    std::ifstream input8("fichier.txt");
    std::getline(input8,ligne,'\n');
    input8.close();
    if (ligne != "Entrer l'id de la tache/sous tache a modifier derrière --id."){
        std::cout<<"Probleme à : Entrer l'id de la tache/sous tache a modifier derrière --id."<<std::endl;
        booleen = false;
    }
    std::ofstream output9("fichier.txt"); 
        //Ne pas avoir un entier derrière --id : "L'identifiant doit être un entier"
        system("./test modify --id carotte close --Terminee > fichier.txt");
    output9.close();
    std::ifstream input9("fichier.txt");
    std::getline(input9,ligne,'\n');
    input9.close();
    if (ligne != "L'identifiant doit être un entier"){
        std::cout<<"Probleme à : L'identifiant doit être un entier"<<std::endl;
        booleen = false;
    }
    std::ofstream output10("fichier.txt"); 
        //Entrer un id ne correspondant à aucun id : "Aucune tache ne correspond à cet identifiant. Vous pouvez obtenir la liste des identifiants en faisant list"
        system("./test modify --id 300 close --Terminee > fichier.txt");
    output10.close();
    std::ifstream input10("fichier.txt");
    std::getline(input10,ligne,'\n');
    input10.close();
    if (ligne != "Aucune tache ne correspond à cet identifiant. Vous pouvez obtenir la liste des identifiants en faisant list"){
        std::cout<<"Probleme à : Aucune tache ne correspond à cet identifiant. Vous pouvez obtenir la liste des identifiants en faisant list"<<std::endl;
        booleen = false;
    }
    std::ofstream output11("fichier.txt"); 
        //Entrer un cinquième terme inconnu : "On ne peut modifier qu'avec les méthodes close, description, title, priority, commentary and undertask."
        system("./test modify --id 1 banane --poire > fichier.txt");
    output11.close();
    std::ifstream input11("fichier.txt");
    std::getline(input11,ligne,'\n');
    input11.close();
    if (ligne != "On ne peut modifier qu'avec les méthodes close, description, title, priority, commentary and undertask."){
        std::cout<<"Probleme à : On ne peut modifier qu'avec les méthodes close, description, title, priority, commentary and undertask."<<std::endl;
        booleen = false;
    }
    std::ofstream output12("fichier.txt"); 
        //Ne pas entrer le sixieme terme sous la forme --suite : "Entrer la suite sous la forme --suite"
        system("./test modify --id 1 description poire > fichier.txt");
    output12.close();
    std::ifstream input12("fichier.txt");
    std::getline(input12,ligne,'\n');
    input12.close();
    if (ligne != "Entrer la suite sous la forme --suite"){
        std::cout<<"Probleme à : Entrer la suite sous la forme --suite"<<std::endl;
        booleen = false;
    }
    std::ofstream output13("fichier.txt"); 
        //Si la methode est close :
            //si le sixieme terme n est pas --Fermee ou --Terminee : "Entrer le statut --Fermee ou --Terminee"
        system("./test modify --id 1 close --poire > fichier.txt");
    output13.close();
    std::ifstream input13("fichier.txt");
    std::getline(input13,ligne,'\n');
    input13.close();
    if (ligne != "Entrer le statut --Fermee ou --Terminee"){
        std::cout<<"Probleme à : Entrer le statut --Fermee ou --Terminee"<<std::endl;
        booleen = false;
    }
    std::ofstream output14("fichier.txt"); 
        //Si la methode n est pas undertask : 
            //Avoir un septieme terme : "Cette methode ne prend pas plus d'arguments, faire attention a utiliser des guillemets en cas d'espaces"
        system("./test modify --id 1 close --poire --melon > fichier.txt");
    output14.close();
    std::ifstream input14("fichier.txt");
    std::getline(input14,ligne,'\n');
    input14.close();
    if (ligne != "Cette methode ne prend pas plus d'arguments, faire attention a utiliser des guillemets en cas d'espaces"){
        std::cout<<"Probleme à : Cette methode ne prend pas plus d'arguments, faire attention a utiliser des guillemets en cas d'espaces"<<std::endl;
        booleen = false;
    }
    std::ofstream output21("fichier.txt"); 
        //Si la methode est undertask (ou qu'on modifie une sous tache) : 
            //Avoir plus de 9999 caractères dans l'un des termes de la sous tache : "Sous tache trop longue : elle ne sera pas conservee en memoire"
    std::string comsoustache ="./test modify --id 1 undertask --title ";
    int indice = 0;
    while (indice<10001){
        comsoustache = comsoustache+"a";
        indice = indice +1;
    }
    comsoustache = comsoustache + "> fichier.txt";
    const char *comsoustachechar = comsoustache.c_str(); 
    system(comsoustachechar);
    output21.close();
    std::ifstream input21("fichier.txt");
    std::getline(input21,ligne,'\n');
    std::getline(input21,ligne,'\n');
    input21.close();
    if (ligne != "Sous tache trop longue : elle ne sera pas conservee en memoire"){
        std::cout<<"Probleme à : Sous tache trop longue : elle ne sera pas conservee en memoire"<<std::endl;
        booleen = false;
    }
    std::ofstream output15("fichier.txt"); 
    //Methode list : 
        //Ne pas respecter la racine --id ou --priority ou --dcreation ou --status ou --percent : "Entrer rien ou --id, --percent, --status, --priority, --dcreation"
        system("./test list priority > fichier.txt");
    output15.close();
    std::ifstream input15("fichier.txt");
    std::getline(input15,ligne,'\n');
    input15.close();
    if (ligne != "Entrer rien ou --id, --percent, --status, --priority, --dcreation"){
        std::cout<<"Probleme à : Entrer rien ou --id, --percent, --status, --priority, --dcreation"<<std::endl;
        booleen = false;
    }
    std::ofstream output16("fichier.txt"); 
        //Si c'est --dcreation
            //Si la date ne comporte pas le bon format : "Entrer la date sous la forme donnee par la notice"
        system("./test list --dcreation 13/01/99 > fichier.txt");
    output16.close();
    std::ifstream input16("fichier.txt");
    std::getline(input16,ligne,'\n');
    input16.close();
    if (ligne != "Entrer la date sous la forme donnee par la notice"){
        std::cout<<"Probleme à : Entrer la date sous la forme donnee par la notice"<<std::endl;
        booleen = false;
    }
    std::ofstream output17("fichier.txt"); 
        system("./test list --dcreation Sun Mar 45 2900 > fichier.txt");
    output17.close();
    std::ifstream input17("fichier.txt");
    std::getline(input17,ligne,'\n');
    input17.close();
    if (ligne != "Entrer la date sous la forme donnee par la notice"){
        std::cout<<"Probleme à : Entrer la date sous la forme donnee par la notice"<<std::endl;
        booleen = false;
    }
    std::ofstream output18("fichier.txt"); 
        //Si c'est --status
            //Si le status n'est pas ouverte, fermee ou terminee : "Le statut ne peut que être Ouverte, Fermee ou Terminee"
        system("./test list --status artichaud > fichier.txt");
    output18.close();
    std::ifstream input18("fichier.txt");
    std::getline(input18,ligne,'\n');
    input18.close();
    if (ligne != "Le statut ne peut que être Ouverte, Fermee ou Terminee"){
        std::cout<<"Probleme à : Le statut ne peut que être Ouverte, Fermee ou Terminee"<<std::endl;
        booleen = false;
    }
    std::ofstream output19("fichier.txt"); 
        //Si c'est --percent
            //Si les 3 premiers caractères ne sont pas equ, inf ou sup ou si la suite n'est pas un float : "Entrer le pourcentage sous la forme signe(equ,inf,sup)+float (cf notice)"
        system("./test list --percent 100 > fichier.txt");
    output19.close();
    std::ifstream input19("fichier.txt");
    std::getline(input19,ligne,'\n');
    input19.close();
    if (ligne != "Entrer le pourcentage sous la forme signe(equ,inf,sup)+float (cf notice)"){
        std::cout<<"Probleme à : Entrer le pourcentage sous la forme signe(equ,inf,sup)+float (cf notice)"<<std::endl;
        booleen = false;
    }
    std::ofstream output20("fichier.txt"); 
        system("./test list --percent infnavet > fichier.txt");
    output20.close();
    std::ifstream input20("fichier.txt");
    std::getline(input20,ligne,'\n');
    input20.close();
    std::cout<<"Malgre toutes les erreurs, on garde la memoire :"<<std::endl;
    system("./test list");

    if (ligne != "Entrer le pourcentage sous la forme signe(equ,inf,sup)+float (cf notice)"){
        std::cout<<"Probleme à : Entrer le pourcentage sous la forme signe(equ,inf,sup)+float (cf notice)"<<std::endl;
        booleen = false;
    }
    
    if (booleen == true){
        std::cout<<"\n //Le programme ne plante pas en fonctionnement anormal."<<std::endl;
    }
    if (booleen == false){
        std::cout<<"\n //Le programme plante en fonctionnement anormal."<<std::endl;
    }

}
    



