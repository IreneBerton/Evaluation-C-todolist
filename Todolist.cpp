 #include <iostream>
 #include <list>
 #include <cstring>
 #include <ctime>
#include <vector>
#include <fstream>

 class Task{
     //Cette tache possède comme attribut : l'identifiant id, le titre title, la description descr,
     //la date de création dcreation, celle de cloture dclosure, le status status, le pourcentage 
     //percent, la priorité priority, la liste de commentaire comm, la liste de sous taches sst, et 
     //également identifiantmax qui correspond à l'identifiant le plus élevé entre celui de la tache
     //et de toutes ses différentes sous taches.
     //Elle a deux constructeurs, l'un qui permet à l'utilisateur de créer des taches, l'autre qui permet
     //de créer les taches après lecture dans un fichier.
     //Elle dispose des méthodes Addcomm (ajoute un commentaire à la liste de commentaires), Addsst
     //(ajoute une tache à la liste de sous taches), Calperc qui calcule le pourcentage en pondérant les 
     //pourcentages des sous taches, Changepriority, Changedescr, Changetitle, Changesst dont le nom est explicite,
     //ainsi que Close qui peut donner le status Fermee ou Terminee à une tache, le dernier cas fixant le 
     //pourcentage de la tache à 100, et enfin Show, qui affiche la tache, et ses sous taches. 
     //On a aussi toutes les méthodes pour accéder aux attributs private. 
     private :
        int id;
        std::string title;
        std::string descr;
        std::string dcreation;
        std::string dclosure;
        std::string status;
        float percent;
        std::string priority;
        std::list<std::string> comm;
        std::list<Task> sst;
        int identifiantmax;
    public :
    Task(int i, std::string t, std::string d, std::string p):id(i),identifiantmax(i),title(t), descr(d),priority(p){
        time_t dc = time(0);
        dcreation = (std::string(ctime(&dc))).substr(0,24);
        dclosure = "On going";
        status = "Ouverte";
        percent = 0;
    }
    Task(int i, std::string t, std::string d,std::string dc, std::string df, std::string st, float per, std::string p, std::list<std::string> co, std::list<Task> s):id(i),title(t),descr(d),dcreation(dc),dclosure(df),status(st),percent(per),priority(p),comm(co),sst(s){
        identifiantmax = i;
        for (std::list<Task>::iterator it = s.begin(); it != s.end(); ++it){
            int a = (*it).identifiantmax;
            if (a>identifiantmax){
                identifiantmax=a;
            }
        }
    }
    void Addcomm(std::string c){
        int n = c.size();
        comm.push_back(c.substr(2,n-2));
    }
    void Addsst(Task t){
        sst.push_back(t);
        if (t.identifiantmax>identifiantmax){
            identifiantmax=t.identifiantmax;
        }
    }
    void Calperc(){
        int s = sst.size();
        if (s != 0){
            for (std::list<Task>::iterator it = sst.begin(); it != sst.end(); ++it){
                (*it).Calperc();
        }
        }
        int somme = 0;
        if (s != 0){
            for (std::list<Task>::iterator it = sst.begin(); it != sst.end(); ++it){
                somme = somme + (*it).percent;
            }
        }
        if (s==0 && status != "Terminee"){
            percent = 0;
        }
        if (s==0 && status == "Terminee"){
            percent = 100;
        }
        if (s != 0){
            percent = somme / s;
        }
        if (percent != 0 && percent != 100){
            status = "En cours";
        }
    }
    void Changepriority(std::string p){
        int n = p.size();
        priority = p.substr(2,n-2);
    }
    void Changedescr(std::string d){
        int n = d.size();
        descr=d.substr(2,n-2);
    }
    void Changetitle(std::string t){
        int n = t.size();
        title=t.substr(2,n-2);
    }
    void Changesst(std::list<Task> s){
        sst = s;
    }
    void Close(std::string arg){
        if (arg=="--Terminee"){
            status = "Terminee";
            percent= 100;
            for (std::list<Task>::iterator it = sst.begin(); it != sst.end(); ++it){
                (*it).Close("--Terminee");
            }
        }
        else {
            status = "Fermee";
            for (std::list<Task>::iterator it = sst.begin(); it != sst.end(); ++it){
                (*it).Close("--Fermee");
        }
        }
        time_t dc = time(0);
        dclosure = (std::string(ctime(&dc))).substr(0,24);
    }
    void Show(){
        std::string strcomm;
        for (std::list<std::string>::iterator it = comm.begin(); it != comm.end(); ++it){
            strcomm = strcomm + (*it) + " // ";
        }
        strcomm = strcomm.substr(0, strcomm.size()-2);
        std::cout<<"id = "<<id;
        std::cout<<" ;\t titre = "<<title<<" ;\t date de création = "<<dcreation<<" ;\t date de fin = "<<dclosure<<" ;\t status = "<<status<<" ;\t percent = "<<percent<<"% ;\t priorité = "<<priority<<" ;\t commentaires = // "<<strcomm<<" ;\t sous tâches = \n {"<<std::endl;
        for (std::list<Task>::iterator it = sst.begin(); it != sst.end(); ++it){
            (*it).Show();
        }
        std::cout<<" }"<<std::endl;
    }
    int Id(){
        return id;
    }
    std::string Title(){
        return title;
    }
    std::string Descr(){
        return descr;
    }
    std::string Dcreation(){
        return dcreation;
    }
    std::string Dclosure(){
        return dclosure;
    }
    std::string Status(){
        return status;
    }
    float Percent(){
        return percent;
    }
    std::string Priority(){
        return priority;
    }
    std::list<std::string> Comm(){
        return comm;
    }
    std::list<Task> Sst(){
        return sst;
    }
    int Identifiantmax(){
        return identifiantmax;
    }
 };

Task liretache(std::ifstream& input){
    //liretache prend en attribut un stream d'un fichier contenant une ligne correspondant à une tache, 
    //et en tire les différents attributs de la tache en question et retourne la tache correspondante. 
    std::string truc;
    int i = 0;
    std::getline(input, truc, '<');
    int id = std::stoi(truc);
    std::getline(input, truc, '<');
    std::string title = truc;
    std::getline(input, truc, '<');
    std::string descr = truc;
    std::getline(input, truc, '<');
    std::string dcreation = truc;
    std::getline(input, truc, '<');
    std::string dclosure = truc;
    std::getline(input, truc, '<');
    std::string status = truc;
    std::getline(input, truc, '<');
    float percent = strtof((truc).c_str(),0);
    std::getline(input, truc, '<');
    std::string priority = truc;
    std::getline(input, truc, '<');
    std::string co = truc;
    //co contient maintenant tous les commentaires séparés entre eux par ">=".
    std::list<std::string> comm;
    std::string delimiter = ">=";
    size_t pos = 0;
    std::string token;
    while ((pos = co.find(delimiter)) != std::string::npos) {
        token = co.substr(0, pos);
        comm.push_back(token);
        co.erase(0, pos + delimiter.length());
    }
    comm.push_back(co);
    std::getline(input, truc, '\n');
    //truc contient maintenant toutes les sous taches, contenues chacune entre accolade,
    //et initiées par le nombre de caractères qu'elles contiennent, stocké sur 4 chiffres.
    std::list<Task> sst;
    std::string delimiter1= "{";
    std::list<std::string> com1;
    std::string b;
    while ((pos = truc.find(delimiter1)) != std::string::npos){
        truc.erase(0,pos + delimiter1.length());
        std::string str = truc.substr(0,4);
        int n = std::stoi(str);
        b = truc.substr(4,n+1);
        truc.erase(0,n+7);
        std::ofstream out("brouillon.txt");
        out<<b<<std::endl;
        out.close();
        std::ifstream brouillon("brouillon.txt");
        sst.push_back(liretache(brouillon));
        brouillon.close();
        std::remove("brouillon.txt");
    }
    //On a maintenant tout pour créer Tache. 
    Task Tache (id,title,descr,dcreation,dclosure,status,percent,priority,comm,sst);
    input.close();
    return Tache;
}

std::list<Task> modifiertache(int argc,char* argv[], int identif, std::list<Task> listetachep){
    //cette fonction retourne la liste de tache modifiée. 
    std::string idstr = argv[3];
    int id = stoi(idstr);
    for (std::list<Task>::iterator it = listetachep.begin(); it != listetachep.end(); ++it){
            std::list<Task> listesstaches= (*it).Sst();
            std::string myst = argv[4];
            //On vérifie que la commande a la bonne forme. 
            if (myst!="close" && myst!="description" && myst!="title" && myst!="priority" && myst!="commentary" && myst!="undertask"){
                std::cout<<"On ne peut modifier qu'avec les méthodes close, description, title, priority, commentary and undertask.";
                return listetachep;
            }
            std::string myst2 = argv[5];
            std::string tirets = myst2.substr(0,2);
            if (tirets != "--"){
                std::cout<<"Entrer la suite sous la forme --suite"<<std::endl;
                return listetachep;
            }
            //On cherche la tache avec le bon identifiant parmis les taches de listetachep, et si 
            //c'est la bonne tache, on cherche la méthode qu'on lui applique et on la lui applique. 
            if ((*it).Id() == id ) {
                if (myst=="close"){
                    if (myst2 != "--Fermee" && myst2 != "--Terminee"){
                        std::cout<<"Entrer le statut --Fermee ou --Terminee"<<std::endl;
                        return listetachep;
                    }
                    (*it).Close(myst2);
                }
                if (myst=="description"){
                    (*it).Changedescr(myst2);
                }
                if (myst=="title"){
                    (*it).Changetitle(myst2);
                }
                if (myst=="priority"){
                    (*it).Changepriority(myst2);
                }
                if (myst=="commentary"){
                    (*it).Addcomm(myst2);
                }
                if (myst=="undertask"){
                    //On répéte le processus de création de tache : 
                    std::string myst0=argv[5];
                    if (myst0!="--title"){
                        std::cout<<"entrer le titre d'abord sous la forme --title puis le titre"<<std::endl;
                        return listetachep;
                    }
                    std::string title=argv[6];
                    std::string descr;
                    std::string prior;
                    if (argc>7){
                        std::string myst=argv[7];
                        std::string myst2=argv[8];
                        if (myst=="--description"){
                            descr=myst2;
                            if (argc>9){
                                std::string myst3 = argv[10];
                                prior=myst3;
                        }
                        }
                        if (myst=="--priority"){
                            prior=myst2;
                            if (argc>9){
                                std::string myst3 = argv[10];
                                descr=myst3;
                            }
                            }
                        if (myst != "--priority" && myst != "--description"){
                            std::cout<<"apres le titre entrer une description et/ou une priorite sous la forme --description ou --priority";
                            return listetachep;
                        }
                        }
                    id = identif + 1;
                    Task nouvelletache(id,title, descr, prior);
                    (*it).Addsst(nouvelletache);
                    std::cout<<"Identifiant de la sous tache ''"<<title<<"'' :"<<id<<std::endl;
                }
            }
            else {
                //Si la tache ne correspond pas, on remplace la liste des sous taches par la liste des sous taches
                //potentiellement modifiée en lui appliquant modifiertache.  
                (*it).Changesst(modifiertache(argc,argv, identif,listesstaches));
                }
            }
    return listetachep;
}

std::string Imprimer(Task t){
    //On cherche à écrire le string qui sera écrit dans le fichier todolist.txt pour stocker la tache. 
    std::string ligne;
    std::string pourcent = std::to_string(t.Percent());
    std::list<std::string> listecom = t.Comm();
    std::string commentaires;
    //On créé le string contenant les commentaires séparés par >=.
    for (std::list<std::string>::iterator it = listecom.begin(); it != listecom.end(); ++it){
        if ((*it).size() != 0){
            commentaires=commentaires + *it + ">=";
        }
        }
    std::string soustaches;
    std::list<Task> listesoustaches= t.Sst();
    //On créé le string contenant les sous taches, en leur appliquant Imprimer une par une, puis
    //en les stockant entre {}, précédés par la longueur du string de la tache stocké sur 4 chiffres. 
    for (std::list<Task>::iterator it = listesoustaches.begin(); it != listesoustaches.end(); ++it){
        std::string soustache = Imprimer(*it);
        int taille = soustache.size();
        soustache = soustache.substr(0,taille-1);
        std::string n = std::to_string(soustache.size());
        if (n.size()>4){
            std::cout<<"Sous tache trop longue : elle ne sera pas conservee en memoire"<<std::endl;
            soustaches=soustaches+"{0009 trop long}>=";
            return "xxx";
        }
            if (n.size()<4){
                if (n.size()==1){
                    n="000"+n;
                }
                if (n.size()==2){
                    n="00"+n;
                }
                if (n.size()==3){
                    n="0"+n;
                }
            }
            soustaches=soustaches + "{"+n+" "+soustache + "}>=";    
        }
    std::string identif = std::to_string(t.Id());
    ligne=identif + '<' + t.Title() + '<' + t.Descr() + '<' + t.Dcreation() + '<' + t.Dclosure() + '<' + t.Status() + '<' + pourcent + '<' + t.Priority() + '<' + commentaires  + '<' + soustaches + '\n';
    return ligne; 
}

int main(int argc,char* argv[]){
    //verifier qu'il y a bien un argument
    if (argc==1){
        std::cout<<"Entrer une methode"<<std::endl;
        return 0;
    }
    std::string methode=argv[1];
    
    //verifier que le premier terme est une methode connue
    if (methode != "reset" && methode != "list" && methode != "modify" && methode != "create"){
        std::cout<<"Methode inconnue"<<std::endl;
        return 0;
    }
     if (methode=="reset"){
        std::remove("todolist.txt");
        return 0;
        }
    std::ifstream input("todolist.txt");
    std::string str;
    //creation de listetachep, qui contiendra toutes les taches et sera modifiée selon les méthodes
    //puis servira a réécrire le fichier.
    std::list<Task> listetachep;
    //si input.is_open(), il y a des taches en memoire que l'on écrit sur lsitetachep.
    if (input.is_open()){
        std::getline(input,str,'\n');
        //On va lire les lignes, chacune correspondant à une tache, une par une.
        while (str.size()!=0){
            std::ofstream out("brouillon.txt");
            out<<str<<std::endl;
            out.close();
            std::ifstream in("brouillon.txt");
            listetachep.push_back(liretache(in));
            in.close();
            std::remove("brouillon.txt");
            std::getline(input,str,'\n');
            std::getline(input,str,'\n');
        }
        input.close();
        }
    
    //On créé identif, qui correspond au plus grand identifiant de toutes les taches. 
    int identif = 0;
    for (std::list<Task>::iterator it = listetachep.begin(); it != listetachep.end(); ++it){
        if ((*it).Identifiantmax() > identif){
            identif=(*it).Identifiantmax();
        }
    }
    if (methode=="create"){
        std::string myst0=argv[2];
        if (myst0!="--title"){
            std::cout<<"Entrer le nouveau titre derriere --title"<<std::endl;
            return 0;
        }
        //On créé les arguments nécessaires à la création d'une nouvelle tache, 
        //puis on cherche si on peut les remplir.
        std::string title=argv[3];
        std::string descr;
        std::string prior;
        if (argc>4){
            if (argc<6){
                std::cout<<"Entrer un priorite ou un commentaire"<<std::endl;
                return 0;
            }
            std::string myst=argv[4];
            std::string myst2=argv[5];
            if (myst=="--description"){
                descr=myst2;
                if (argc>6){
                    if (argc<8){
                        std::cout<<"Entrer un priorite ou un commentaire"<<std::endl;
                        return 0;
                    }
                    std::string myst4 = argv[6];
                    if (myst4 != "--priority"){
                        std::cout<<"Format non respecte, cf doc"<<std::endl;
                        return 0;
                    }
                    std::string myst3=argv[7];
                    prior=myst3;
                }
            }
            if (myst=="--priority"){
                prior=myst2;
                if (argc>6){
                    if (argc<8){
                        std::cout<<"Entrer un priorite ou un commentaire"<<std::endl;
                        return 0;
                    }
                    std::string myst4 = argv[6];
                    if (myst4 != "--description"){
                        std::cout<<"Format non respecte, cf doc"<<std::endl;
                        return 0;
                    }
                    std::string myst3=argv[7];
                    descr=myst3;
                }
            }
            if ((myst!="--priority") && (myst!="--description")) {
                std::cout<<"Format non respecte, cf doc";
                return 0;
            }
            }
        //On trouve id à partir de identif puis  on créé un nouvelle tache qu'on ajoute à listetachep
        int id=identif + 1;
        Task nouvelletache(id,title, descr, prior);
        listetachep.push_back(nouvelletache);
        std::cout<<"Identifiant de la tache ''"<<title<<"'' :"<<id<<std::endl;
    }
    if (methode=="list"){
        int i=2;
        //On créé la liste alister, qui contient toutes les taches à lister. 
        std::list<Task> alister;
        //Si il n'y a que deux arguments, il faut tout lister.
        if (argc==2){
            alister=listetachep;
            }
        //Sinon, il faut reconnaitre les "filtres"; i correspond à l'indice des termes en commande que l'on observe.
        while (i<argc){
            std::string myst=argv[i];
            if (myst=="--id"){
                std::string idstr=argv[i+1];
                int id = std::stoi(idstr);
                for (std::list<Task>::iterator it = listetachep.begin(); it != listetachep.end(); ++it){
                    if ((*it).Id() == id){
                        alister.push_back(*it);
                    }
                }
                i=i+2;
            }
            if (myst=="--priority"){
                std::string prior=argv[i+1];
                for (std::list<Task>::iterator it = listetachep.begin(); it != listetachep.end(); ++it){
                    if ((*it).Priority() == prior){
                        alister.push_back(*it);
                    }
                }
                i=i+2;
            }
            if (myst=="--status"){
                std::string stat=argv[i+1];
                if (stat != "Ouverte" && stat != "Fermee" && stat != "Terminee"){
                    std::cout<<"Le statut ne peut que être Ouverte, Fermee ou Terminee"<<std::endl;
                    return 0;
                }
                for (std::list<Task>::iterator it = listetachep.begin(); it != listetachep.end(); ++it){
                    if ((*it).Status() == stat){
                        alister.push_back(*it);
                }
                }
                i=i+2;
            }
            if (myst=="--percent"){
                std::string strperctot = argv[i+1];
                if (strperctot.size()<4){
                    std::cout<<"Entrer le pourcentage sous la forme signe(equ,inf,sup)+float (cf notice)"<<std::endl;
                    return 0;
                }
                std::string signe = strperctot.substr(0,3);
                std::string strperc = strperctot.substr(3,strperctot.size()-3);
                float perc = 0;
                try {
                    perc = std::stof(strperc);
                }
                catch(...){
                    std::cout<<"Entrer le pourcentage sous la forme signe(equ,inf,sup)+float (cf notice)"<<std::endl;
                    return 0;
                }
                for (std::list<Task>::iterator it = listetachep.begin(); it != listetachep.end(); ++it){
                    if (signe == "equ"){
                        if ((*it).Percent() == perc){
                            alister.push_back(*it);
                        }
                    }
                    if (signe == "inf"){
                        if ((*it).Percent() <= perc){
                            alister.push_back(*it);
                        }
                    }
                    if (signe == "sup"){
                        if ((*it).Percent() >= perc){
                            alister.push_back(*it);
                        }
                    }
                    if (signe != "inf" && signe != "sup" && signe != "equ"){
                        std::cout<<"Entrer le pourcentage sous la forme signe(equ,inf,sup)+float (cf notice)"<<std::endl;
                    }
                }
                i=i+2;
            }
            if (myst=="--dcreation"){
                std::string ladate = argv[i+1];
                //on vérifie que la date est sous la bonne forme.
                try{
                    std::string jour = ladate.substr(0,3);
                    std::string mois = ladate.substr(4,3);
                    std::string num = ladate.substr(8,2);
                    std::string annee = ladate.substr(11,4);
                    int numint = std::stoi(num);
                    int anneeint = std::stoi(annee); 
                }
                catch(...){
                    std::cout<<"Entrer la date sous la forme donnee par la notice"<<std::endl;
                    return 0;
                }
                std::string jour = ladate.substr(0,3);
                std::string mois = ladate.substr(4,3);
                std::string num = ladate.substr(8,2);
                std::string annee = ladate.substr(11,4);
                int numint = std::stoi(num);
                int anneeint = std::stoi(annee);
                if (jour != "Mon" && jour != "Tue" && jour != "Wen" && jour != "Thu" && jour != "Fri" && jour != "Sat" && jour != "Sun"){
                    std::cout<<"Entrer la date sous la forme donnee par la notice"<<std::endl;
                    return 0;
                }
                if (mois != "Jan" && mois != "Feb" && mois != "Mar" && mois != "Apr" && mois != "May" && mois != "Jun" && mois != "Jul" && mois != "Aug" && mois != "Sep" && mois != "Oct" && mois != "Nov" && mois != "Dec"){
                    std::cout<<"Entrer la date sous la forme donnee par la notice"<<std::endl;
                    return 0;
                }
                //Maintenant on cherche les taches créées le jour indiqué.
                for (std::list<Task>::iterator it = listetachep.begin(); it != listetachep.end(); ++it){
                    std::string datetache = (*it).Dcreation();
                    std:: string date = datetache.substr(0,10) + " " +datetache.substr(20, datetache.size() - 20);
                    if (date == ladate){
                        alister.push_back(*it);
                }
                }
                i=i+6;
            }
            if (myst != "id" && myst != "--dcreation" && myst != "--percent" && myst != "--status" && myst != "--priority"){
                std::cout<<"Entrer rien ou --id, --percent, --status, --priority, --dcreation"<<std::endl;
                break;
            }
        }
        //On print toutes les taches à lister
        if (listetachep.size() ==0){
            std::cout<<"Liste vide";
            return 0;
        }
        for (std::list<Task>::iterator it = alister.begin(); it != alister.end(); ++it){
            std::cout<<"\n"<<"tache ''"<<(*it).Title()<<"'' :"<<std::endl;
            std::cout<<"\n"<<std::endl;
            (*it).Show();
        }   
    }
    if (methode=="modify"){
        //On verifie que modifie a globalement la bonne structure.
        if (argc < 6){
            std::cout<<"Le format de la methode modify n'est pas respecte."<<std::endl;
            return 0;
        }
        std::string myst1 = argv[4];
        if (myst1 != "undertask" && argc > 6){
            std::cout<<"Cette methode ne prend pas plus d'arguments, faire attention a utiliser des guillemets en cas d'espaces"<<std::endl;
            return 0;
        }
        std::string myst= argv[2];
        if (myst!="--id"){
            std::cout<<"Entrer l'id de la tache/sous tache a modifier derrière --id.";
            return 0;
        }
        std::string idstr = argv[3];
        int id;
        try{
            id = stoi(idstr);
        }
        catch(...){
            std::cout<<"L'identifiant doit être un entier"<<std::endl;
            return 0;
        }
        if (id > identif){
            std::cout<<"Aucune tache ne correspond à cet identifiant. Vous pouvez obtenir la liste des identifiants en faisant list"<<std::endl;
            return 0;
        }
        //on modifie la tache grâce à la fonction modifiertache
        listetachep = modifiertache(argc,argv, identif, listetachep);
        std::string myst0 = argv[4];
    }     
    if (methode != "modify" && methode != "list" && methode != "create"){
        std::cout<<"methode non connue"<<std::endl;
        return 0;
    }
    //On supprime le fichier mémoire todolist.txt pour le recréer et le reremplir par la suite
    std::ifstream source("todolist.txt", std::ios::binary);
    std::ofstream copy("todolistsecours.txt",   std::ios::binary);
    copy << source.rdbuf();
    input.close();
    copy.close();
    std::remove("todolist.txt");
    std::ofstream out("todolist.txt");
    //On va parcourir lsitetachep, recalculer les pourcentages de toutes les taches car ils ont pu
    //être modifiés par les opérations effectuées, puis imprimer dans le nouveau fichier vide.
    for (std::list<Task>::iterator it = listetachep.begin(); it != listetachep.end(); ++it){
        (*it).Calperc();
        std::string ligne = Imprimer(*it);
        if (ligne == "xxx"){
            out.close();
            std::remove("todolist.txt");
            std::ifstream source2("todolistsecours.txt", std::ios::binary);
            std::ofstream copy2("todolist.txt", std::ios::binary);
            copy2 << source2.rdbuf();
            input.close();
            copy.close();
            std::remove("todolistsecours.txt");
            break;
        }
        out<<ligne<<std::endl;
        }
    out.close();
    return 0;
 }

