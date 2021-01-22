#include <iostream>
#include <vector>
#include <fstream>
#include <unistd.h>
#include <stdio.h>
#include <chrono>
#include <ctime>
#include <map>
#include <sstream>
using namespace std;
typedef long long ll;
typedef long double ld;
bool const QST = true;
bool const ANS = false;
map<string,ll>month;
struct node {
    bool stat;
    string data;
    ll par;
    ll rtn;
    ll wan;
    ll ple;
};
struct seacont {
    node data;
    ld rela;
};
struct stc {
    string data;
    bool rtn;
};
struct trfl {
    string name;
    string create;
    string mod;
    ll size;
};
struct bkimp {
    string name;
    ll action;
};
string ask() {
    string res = "";
    while (res!="y"&&res!="n") {
        getline(cin,res);
        transform(res.begin(),res.end(),res.begin(),::tolower);
        if (res!="y"&&res!="n") {
            cout<<"Invalid answer!"<<endl;
        }
    }
    return res;
}
string user = getlogin();
string libpath = "/Users/"+user+"/Library/Application Support/ClassificationTree/";
string pth(string target) {
    return libpath+target;
}
string file;
bool isint(string x) {
    if (x==to_string(atoll(x.c_str()))) {
        return true;
    }
    return false;
}
bool srcmp(seacont const &a,seacont const &b) {
    if (a.rela>b.rela) {
        return true;
    }
    return false;
}
bool fcopy(string from,string to) {
    ifstream in(from);
    ofstream out(to);
    string s;
    if (in.good()&&out.good()) {
        out<<in.rdbuf();
    } else {
        in.close();
        out.close();
        return 1;
    }
    in.close();
    out.close();
    return 0;
}
bool cmp(ll a,ll b) {
    if (a>b) {
        return true;
    }
    return false;
}
ll ec;
ofstream out;
vector<node>tree;
void dfs(ll n,vector<ll> &tbd) {
    if (tree[n].stat==QST) {
        dfs(tree[n].rtn,tbd);
        dfs(tree[n].wan,tbd);
    }
    tbd.push_back(tree[n].ple);
}
string date() {
    time_t tmptime = chrono::system_clock::to_time_t(chrono::system_clock::now());
    string tmp = ctime(&tmptime);
    tmp.erase(tmp.size()-1,1);
    return tmp;
}
long long const INC_ALPHA = 0;
long long const DESC_ALPHA = 1;
long long const INC_DATE_CRE = 2;
long long const DESC_DATE_CRE = 3;
long long const INC_DATE_MOD = 4;
long long const DESC_DATE_MOD = 5;
long long const INC_SIZE = 6;
long long const DESC_SIZE = 7;
ll sortmode;
bool comp(trfl const &x, trfl const &y) /* Directory list custom sort */ {
    if (sortmode==INC_ALPHA) {
        if (x.name<y.name) {
            return true;
        } else {
            return false;
        }
    } else if (sortmode==DESC_ALPHA) {
        if (x.name>y.name) {
            return true;
        } else {
            return false;
        }
    } else if (sortmode==INC_DATE_CRE||sortmode==DESC_DATE_CRE||sortmode==INC_DATE_MOD||sortmode==DESC_DATE_MOD) {
        ll xyear,xmonth,xday,xhour,xmin,xsec,yyear,ymonth,yday,yhour,ymin,ysec;
        string a = x.mod;
        if (sortmode==INC_DATE_CRE||sortmode==DESC_DATE_CRE) {
            a=x.create;
        }
        a.erase(0,a.find(' ')+1);
        xmonth=month[a.substr(0,3)];
        a.erase(0,a.find(' ')+1);
        xday=atoll(a.substr(0,a.find(' ')).c_str());
        a.erase(0,a.find(' ')+1);
        xhour=atoll(a.substr(0,a.find(':')).c_str());
        a.erase(0,a.find(':')+1);
        xmin=atoll(a.substr(0,a.find(':')).c_str());
        a.erase(0,a.find(':')+1);
        xsec=atoll(a.substr(0,a.find(' ')).c_str());
        a.erase(0,a.find(' ')+1);
        xyear=atoll(a.c_str());
        string b = y.mod;
        if (sortmode==INC_DATE_CRE||sortmode==DESC_DATE_CRE) {
            b=y.create;
        }
        b.erase(0,b.find(' ')+1);
        ymonth=month[b.substr(0,3)];
        b.erase(0,b.find(' ')+1);
        yday=atoll(b.substr(0,b.find(' ')).c_str());
        b.erase(0,b.find(' ')+1);
        yhour=atoll(b.substr(0,b.find(':')).c_str());
        b.erase(0,b.find(':')+1);
        ymin=atoll(b.substr(0,b.find(':')).c_str());
        b.erase(0,b.find(':')+1);
        ysec=atoll(a.substr(0,b.find(' ')).c_str());
        b.erase(0,b.find(' ')+1);
        yyear=atoll(b.c_str());
        if (xyear<yyear) {
            if (sortmode==INC_DATE_CRE||sortmode==INC_DATE_MOD) {
                return true;
            } else {
                return false;
            }
        } else if (xyear>yyear) {
            if (sortmode==INC_DATE_CRE||sortmode==INC_DATE_MOD) {
                return false;
            } else {
                return true;
            }
        } else {
            if (xmonth<ymonth) {
                if (sortmode==INC_DATE_CRE||sortmode==INC_DATE_MOD) {
                    return true;
                } else {
                    return false;
                }
            } else if (xmonth>ymonth) {
                if (sortmode==INC_DATE_CRE||sortmode==INC_DATE_MOD) {
                    return false;
                } else {
                    return true;
                }
            } else {
                if (xday<yday) {
                    if (sortmode==INC_DATE_CRE||sortmode==INC_DATE_MOD) {
                        return true;
                    } else {
                        return false;
                    }
                } else if (xday>yday) {
                    if (sortmode==INC_DATE_CRE||sortmode==INC_DATE_MOD) {
                        return false;
                    } else {
                        return true;
                    }
                } else {
                    if (xmin<ymin) {
                        if (sortmode==INC_DATE_CRE||sortmode==INC_DATE_MOD) {
                            return true;
                        } else {
                            return false;
                        }
                    } else if (xmin>ymin) {
                        if (sortmode==INC_DATE_CRE||sortmode==INC_DATE_MOD) {
                            return false;
                        } else {
                            return true;
                        }
                    } else {
                        if (xsec<ysec) {
                            if (sortmode==INC_DATE_CRE||sortmode==INC_DATE_MOD) {
                                return true;
                            } else {
                                return false;
                            }
                        } else {
                            if (sortmode==INC_DATE_CRE||sortmode==INC_DATE_MOD) {
                                return false;
                            } else {
                                return true;
                            }
                        }
                    }
                }
            }
        }
    } else if (sortmode==INC_SIZE) {
        if (x.size<y.size) {
            return true;
        } else {
            return false;
        }
    } else if (sortmode==DESC_SIZE) {
        if (x.size>y.size) {
            return true;
        } else {
            return false;
        }
    }
    return false;
}
bool customlib = false;
bool beta = true;
int main() {
    month["Jan"]=1;
    month["Feb"]=2;
    month["Mar"]=3;
    month["Apr"]=4;
    month["May"]=5;
    month["Jun"]=6;
    month["Jul"]=7;
    month["Aug"]=8;
    month["Sep"]=9;
    month["Oct"]=10;
    month["Nov"]=11;
    month["Dec"]=12;
    ifstream in;
    string name;
    vector<trfl>dir;
    bool setup = false;
    bool init = true;
    if (beta) {
        cout<<endl<<"ALERT! You are running the developer build! This means that features may not be complete and features marked as still in development should NOT be used and can cause irreversable damage to your tree files. Newer versions of the beta may not be compatible with older versions."<<endl;
    }
    cout<<endl<<"Welcome to the Binary Classification Tree! Made by LegitMichel777. BCTv2.0 BETA,TFSv3.0."<<endl;
    while (init) /* Start */ {
        init = false;
        cout<<"Loading directories..."<<endl;
        in.open("/Users/"+user+"/Library/Application Support/ClassificationTree/pos.redir");
        if (in.good()) {
            getline(in,libpath);
            customlib = true;
        }
        in.close();
        in.open(pth("contents.man"));
        if (in.good()) {
            string getdirsort;
            if (!in.eof()) {
                getline(in,getdirsort);
                sortmode = atoll(getdirsort.c_str());
            }
            while (!in.eof()) {
                string create;
                string mod;
                string size;
                ll trusize;
                getline(in,name);
                if (name=="") {
                    break;
                }
                if (!in.eof()) {
                    getline(in,create);
                } else {
                    cout<<"Read error! Error code CDATE"<<endl;
                    break;
                }
                if (!in.eof()) {
                    getline(in,mod);
                } else {
                    cout<<"Read error! Error code MDATE"<<endl;
                    break;
                }
                if (!in.eof()) {
                    getline(in,size);
                    trusize = atoll(size.c_str());
                } else {
                    cout<<"Read error! Error code SIZE"<<endl;
                    break;
                }
                dir.push_back((trfl){name,create,mod,trusize});
            }
        } else { //MARK:Newbie
            if (!customlib) {
                string cmd = "/Users/" +user+"/Library/Application\\ Support/ClassificationTree";
                cmd = "mkdir "+cmd;
                system(cmd.c_str());
                cout<<"Hello there! Welcome to the Binary Search Tree! The Tree is an extremely powerful utility. For example, with only 15 questions, you can classify up to 32,768 objects! Your files are saved to your application support inside a folder called ClassificationTree. Some app cleaners might see this as trash, so beware of accidentally deleting the folder. To get started, answer the questions and create your very first Binary Search Tree!"<<endl;
            } else {
                cout<<"Error! File cotents not found. You can:"<<endl<<"[1]Enter a custom directory to laod up"<<endl<<"[2]Use default directory"<<endl;
                string resconerr;
                while (true) {
                    getline(cin,resconerr);
                    if (resconerr=="1"||resconerr=="2") {
                        break;
                    }
                    cout<<"Invalid answer!"<<endl;
                }
                if (resconerr=="1") {
                    string errdir;
                    getline(cin,errdir);
                    out.open("/Users/"+user+"/Library/Application Support/ClassificationTree/pos.redir");
                    if (out.good()) {
                        out<<errdir;
                        cout<<"Directory position successfully changed. Reloading..."<<endl;
                    } else {
                        cout<<"Error accessing redirect file! Please try again later."<<endl;
                    }
                    out.close();
                    init = true;
                } else {
                    if ((ec=remove(("/Users/"+user+"/Library/Application Support/ClassificationTree/pos.redir").c_str()))) {
                        cout<<"Error removing redirect! Please try again later."<<endl;
                        init = true;
                    } else {
                        cout<<"Directory position successfully changed. Reloading..."<<endl;
                    }
                }
            }
        }
        in.close();
    }
    for (ll i=0;i<dir.size();i++) /* Validate */ {
        in.open(pth(dir[i].name+".tree"));
        if (!in.good()) {
            cout<<"Error while validating "<<dir[i].name<<". It has been removed from the directory list. This might be because the file is deleted or currently inaccessible. If it is currently inaccessible, you can import it from ~/Library/ClassificationTree/"<<endl;
            dir.erase(dir.begin()+i);
            i--;
        }
        in.close();
    }
    while (true) { //MARK: Start
        setup = false;
        bool cond = true;
        ll fpoint=-1;
        string dname;
        while (cond) {
            sort(dir.begin(),dir.end(),comp);
            cout<<"Enter ID of save to open, action to preform or enter anything else to end the program..."<<endl;
            cout<<"[1]Create new"<<endl<<"[2]Import"<<endl;
            for (ll i=3;i<=dir.size()+2;i++) {
                cout<<'['<<i<<']'<<dir[i-3].name<<endl;
            }
            cout<<"["<<dir.size()+3<<"]"<<"Settings"<<endl;
            bool treeop=true;
            getline(cin,file);
            if (isint(file)) {
                if (atoll(file.c_str())<1&&atoll(file.c_str())>2+dir.size()) {
                    out.open(pth("contents.man"));
                    out<<sortmode<<endl;
                    for (ll i=0;i<dir.size();i++) {
                        out<<dir[i].name<<endl<<dir[i].create<<endl<<dir[i].mod<<endl<<dir[i].size<<endl;
                    }
                    out.close();
                    return 0;
                }
                if (file=="1") /* New */{
                    tree.clear();
                    treeop = false;
                    setup = true;
                    break;
                }
                else if (file=="2") /* Import */ {
                    treeop=false;
                    cout<<"What is the path of the file you want to import?"<<endl;
                    string pin;
                    getline(cin,pin);
                    string impname;
                    for (ll i=0;i<pin.size();i++) {
                        if (pin[i]=='/') {
                            impname = "";
                        } else {
                            impname = impname+pin[i];
                        }
                    }
                    if (impname.find(';')!=string::npos||impname.find(':')!=string::npos) {
                        cout<<"Error! File names cannot contain : and ;. Please rename the file and try again."<<endl;
                    } else {
                        if ((ec=impname[impname.size()-1]=='e'&&impname[impname.size()-2]=='e'&&impname[impname.size()-3]=='r'&&impname[impname.size()-4]=='t'&&impname[impname.size()-5]=='.')) {
                            impname = impname.substr(0,impname.length()-5);
                            ll overlap = -1;
                            for (ll i=0;i<dir.size();i++) {
                                if (dir[i].name==impname) {
                                    overlap = i;
                                    break;
                                }
                            }
                            if (overlap!=-1) {
                                cout<<dir[overlap].name<<" already exists in your directory list. Do you want to:"<<endl<<"[1]Keep both"<<endl<<"[2]Do not copy"<<endl<<"[3]Replace"<<endl;
                                string overimpres;
                                while (true) {
                                    getline(cin,overimpres);
                                    if (overimpres=="1"||overimpres=="2"||overimpres=="3") {
                                        break;
                                    }
                                    cout<<"Invalid answer!"<<endl;
                                }
                                if (overimpres=="1") {
                                    ll testitr = 1;
                                    while (testitr++) {
                                        string totest = dir[overlap].name+" "+to_string(testitr);
                                        bool ok = true;
                                        for (ll i=0;i<dir.size();i++) {
                                            if (dir[i].name==totest) {
                                                ok = false;
                                                break;
                                            }
                                        }
                                        if (ok) {
                                            break;
                                        }
                                    }
                                    in.open(pin);
                                    if (in.good()) {
                                        if ((ec = fcopy(pin,libpath+impname+" "+to_string(testitr)+".tree"))) {
                                            cout<<"An error occured while importing the tree. Error code "<<ec<<"."<<endl;
                                        } else {
                                            ll impsize = 0;
                                            string tmp;
                                            while (!in.eof()) {
                                                getline(in,tmp);
                                                impsize++;
                                            }
                                            dir.push_back((trfl){impname+" "+to_string(testitr),date(),date(),impsize});
                                        }
                                    } else {
                                        cout<<"An error occured while accessing the tree you're trying to import. Please try again later."<<endl;
                                    }
                                    in.close();
                                } else if (overimpres=="3") {
                                    in.open(pin);
                                    if (in.good()) {
                                        dir[overlap].mod=dir[overlap].create=date(); //Fix it
                                        remove(pth(dir[overlap].name+".tree").c_str());
                                        if ((ec=fcopy(pin,libpath+impname+".tree"))) {
                                            cout<<"An error occured while importing the tree. Error code "<<ec<<". This should not have happened. Sorry, your older file is now lost."<<endl;
                                        } else {
                                            ll impsize = 0;
                                            string tmp;
                                            while (!in.eof()) {
                                                getline(in,tmp);
                                                impsize++;
                                            }
                                        }
                                    } else {
                                        cout<<"An error occured while accessing the tree you're trying to import. Please try again later."<<endl;
                                    }
                                    in.close();
                                }
                            } else {
                                if ((ec=fcopy(pin,libpath+impname+".tree"))) {
                                    cout<<"An error occured while importing the tree. Error code "<<ec<<'.'<<endl;
                                    remove((libpath+impname+".tree").c_str());
                                } else {
                                    in.open(pin);
                                    ll impsize = 0;
                                    string tmp;
                                    while (!in.eof()) {
                                        getline(in,tmp);
                                        impsize++;
                                    }
                                    in.close();
                                    impsize--;
                                    impsize = impsize/2;
                                    dir.push_back((trfl){impname,date(),date(),impsize});
                                    cout<<impname<<" imported successfully."<<endl;
                                }
                            }
                        } else {
                            cout<<"Invalid file type!"<<endl;
                        }
                    }
                }
                else if (atoll(file.c_str())>=3&&atoll(file.c_str())<=2+dir.size()) /* Opening tree */ {
                    dname = dir[atoll(file.c_str())-3].name;
                    fpoint =atoll(file.c_str())-3;
                    file = pth(dir[atoll(file.c_str())-3].name+".tree");
                }
                else if (atoll(file.c_str())==dir.size()+3) {
                    treeop=false;
                    string inp;
                    cout<<"What would you like to do?"<<endl<<"[1]Change directory sort order"<<endl<<"[2]Clear all data"<<endl<<"[3]Create backup"<<endl<<"[4]Import backup (Still in development)"<<endl<<"[5]Change directory position"<<endl;
                    if (customlib) /* Output options for custom library */ {
                        cout<<"[6]Switch to deafult directory position"<<endl<<"[7]Nothing"<<endl;
                        while (true) {
                            getline(cin,inp);
                            if (isint(inp)) {
                                if (atoll(inp.c_str())<=7&&atoll(inp.c_str())>=1) {
                                    break;
                                }
                            }
                            cout<<"Invalid answer!"<<endl;
                        }
                    } else {
                        cout<<"[6]Nothing"<<endl;
                        while (true) {
                            getline(cin,inp);
                            if (isint(inp)) {
                                if (atoll(inp.c_str())<=6&&atoll(inp.c_str())>=1) {
                                    break;
                                }
                            }
                            cout<<"Invalid answer!"<<endl;
                        }
                    }
                    if (inp=="1") /* Settings-Dir sort */ {
                        cout<<"What sort order would you like?"<<endl<<"[1]Alphabetical order, increasing."<<endl<<"[2]Alphabetical order, descending."<<endl<<"[3]Date created, increasing."<<endl<<"[4]Date created, descending."<<endl<<"[5]Date modified, increasing."<<endl<<"[6]Date modified, descending."<<endl<<"[7]Size, increasing."<<endl<<"[8]Size, descending."<<endl;
                        string sortres;
                        while (true) {
                            getline(cin,sortres);
                            if (isint(sortres)) {
                                if (atoll(sortres.c_str())>=1&&atoll(sortres.c_str())<=8) {
                                    sortmode = atoll(sortres.c_str())-1;
                                    break;
                                }
                            }
                            cout<<"Invalid answer!"<<endl;
                        }
                        cout<<"Sort mode successfully set."<<endl;
                    }
                    else if (inp=="2") /* Settings-Clear data */{
                        cout<<"Are you sure you want to clear all data? This action is irreversible. (y or n)"<<endl;
                        string erall=ask();
                        vector<ll>successtmp;
                        if (erall=="y") {
                            for (ll i=0;i<dir.size();i++) {
                                if ((ec=remove((libpath+dir[i].name+".tree").c_str()))) {
                                    cout<<"A error occured while deleting tree "<<dir[i].name<<". Error code "<<ec<<'.'<<endl;
                                } else {
                                    successtmp.push_back(i);
                                }
                            }
                            for (ll i=0;i<successtmp.size();i++) {
                                dir.erase(dir.begin()+successtmp[i]-i);
                            }
                            cout<<"Trees deleted successfully."<<endl;
                        }
                    }
                    else if (inp=="3") /* Settings-Create backup */ {
                        cout<<"Where would you like to backup your data to?"<<endl;
                        string backupdst;
                        getline(cin,backupdst);
                        backupdst = backupdst+"/backup.libbackup";
                        out.open(backupdst);
                        if (out.good()) {
                            out<<":BACKUP:contents.man"<<endl;
                            string backup;
                            in.open(pth("contents.man"));
                            while (!in.eof()) {
                                getline(in,backup);
                                if (backup!="") {
                                    out<<backup<<endl;
                                }
                            }
                            in.close();
                            out<<";BACKUP;contents.man"<<endl;
                            for (ll i=0;i<dir.size();i++) {
                                out<<":BACKUP:"<<dir[i].name<<".tree"<<endl;
                                in.open(pth(dir[i].name+".tree"));
                                if (in.good()) {
                                    while (!in.eof()) {
                                        getline(in,backup);
                                        if (backup!="") {
                                            out<<backup<<endl;
                                        }
                                    }
                                    out<<";BACKUP;"<<dir[i].name<<".tree"<<endl;
                                } else {
                                    cout<<"Error backing up "<<dir[i].name<<". Please try again later."<<endl;
                                }
                                in.close();
                            }
                            cout<<"Backup complete."<<endl;
                        } else {
                            cout<<"Error writing to file.";
                        }
                        out.close();
                    }
                    else if (inp=="4") /* Settings-Backup */ {
                        /*
                         Merge with current.
                         If there's an identical one:
                         [DIR] already exists in your directory list. Do you want to:
                         [1]Keep both
                         [2]Do not copy
                         [3]Replace
                         */
                        cout<<"What is the path of the backup you want to import?"<<endl;
                        string backuppath;
                        getline(cin,backuppath);
                        in.open(backuppath);
                        vector<bkimp>resback;
                        if (in.good()) {
                            string gbkc;
                            getline(in,gbkc);
                            string restsm;
                            if (gbkc==":BACKUP:contents.man") {
                                getline(in,restsm);
                                if (restsm=="0") cout<<"Would you like to sort trees by alphabetical order(increasing)?"<<endl;
                                else if (restsm=="1") cout<<"Would you like to sort trees by alphabetical order(decreasing)?"<<endl;
                                else if (restsm=="2") cout<<"Would you like to sort trees by date created(increasing)?"<<endl;
                                else if (restsm=="3") cout<<"Would you like to sort trees by date created(decreasing)?"<<endl;
                                else if (restsm=="4") cout<<"Would you like to sort trees by date modified(increasing)?"<<endl;
                                else if (restsm=="5") cout<<"Would you like to sort trees by date modified(decreasing)?"<<endl;
                                else if (restsm=="6") cout<<"Would you like to sort trees by size(increasing)?"<<endl;
                                else cout<<"Would you like to sort trees by size(decreasing)?"<<endl;
                                while (true) {
                                    getline(in,gbkc); //Get name
                                    string datecre,datemod,bksize;
                                    if (gbkc==";BACKUP;contents.man") {
                                        break;
                                    }
                                    ll overlap = -1;
                                    for (ll i=0;i<dir.size();i++) {
                                        if (gbkc==dir[i].name) {
                                            overlap = i;
                                            break;
                                        }
                                    }
                                    getline(in,datecre);
                                    getline(in,datemod);
                                    getline(in,bksize);
                                    if (overlap!=-1) {
                                        cout<<dir[overlap].name<<" already exists in your directory list. Do you want to:"<<endl<<"[1]Keep both"<<endl<<"[2]Do not copy"<<endl<<"[3]Replace"<<endl;
                                        string bkdes;
                                        while (true) {
                                            getline(cin,bkdes);
                                            if (bkdes=="1"||bkdes=="2"||bkdes=="3") {
                                                break;
                                            }
                                            cout<<"Invlid answer!"<<endl;
                                        }
                                        if (bkdes=="1") {
                                            ll testitr = 1;
                                            while (testitr++) {
                                                string totest = gbkc+" "+to_string(testitr);
                                                bool ok = true;
                                                for (ll i=0;i<dir.size();i++) {
                                                    if (dir[i].name==totest) {
                                                        ok = false;
                                                        break;
                                                    }
                                                }
                                                if (ok) {
                                                    break;
                                                }
                                            }
                                            resback.push_back((bkimp){gbkc,testitr});
                                        } else if (bkdes=="3") {
                                            //Delete original file and import new
                                            resback.push_back((bkimp){gbkc,-2});
                                        }
                                    } else {
                                        //Import
                                        dir.push_back((trfl){gbkc,datecre,datemod,atoll(bksize.c_str())});
                                        resback.push_back((bkimp){gbkc,-1});
                                    }
                                }
                                //Parse backup and preform actions
                                //Action 0:Do not import
                                //Action +:Keep both
                                //Action -1:Just do it
                                //Action -2:Replace
                            } else {
                                cout<<"Error! Invalid file."<<endl;
                            }
                        } else {
                            cout<<"Error accessing backup."<<endl;
                        }
                        in.close();
                    }
                    else if (inp=="5") /* Settings-Move library */ {
                        cout<<"Where would you like the library to be moved to?"<<endl;
                        string dst;
                        getline(cin,dst);
                        stringstream ss;
                        for (ll i=0;i<dst.size();i++) {
                            if (dst[i]==' ') {
                                ss<<"\\ ";
                            } else {
                                ss<<dst[i];
                            }
                        }
                        string syscmd;
                        getline(ss,syscmd);
                        syscmd = "mkdir "+dst+"/ClassificationTree";
                        dst = dst+"/ClassificationTree";
                        system(syscmd.c_str());
                        dst = dst+'/';
                        if ((ec=fcopy(pth("contents.man"),dst+"contents.man"))) {
                            cout<<"An error occured while moving contents. Error code "<<ec<<"."<<endl;
                        } else {
                            out.open("/Users/"+user+"/Library/Application Support/ClassificationTree/pos.redir");
                            out<<dst;
                            out.close();
                            if ((ec=remove(pth("contents.man").c_str()))) {
                                cout<<"An error occured while removing contents. Error code "<<ec<<". Directory position changed failed."<<endl;
                            }
                            for (ll i=0;i<dir.size();i++) {
                                if ((ec=fcopy(pth(dir[i].name+".tree"),dst+dir[i].name+".tree"))) {
                                    cout<<"An error occured while moving "<<dir[i].name<<". Error code "<<ec<<"."<<endl;
                                } else {
                                    if ((ec=remove((pth(dir[i].name)+".tree").c_str()))) {
                                        cout<<"An error occured while removing "<<dir[i].name<<". Error code "<<ec<<"."<<endl;
                                    }
                                }
                            }
                            if (customlib) {
                                if ((ec = rmdir(libpath.substr(0,libpath.length()-1).c_str()))) {
                                    cout<<"An error occured while deleting the old directory. Error code "<<ec<<"."<<endl;
                                }
                            } else {
                                customlib=true;
                            }
                            libpath = dst;
                            cout<<"Library position successfully changed."<<endl;
                        }
                    }
                    else if (inp=="6") /* Settings-Restore default library */ {
                        if (customlib) {
                            if ((ec=remove(("/Users/"+user+"/Library/Application Support/ClassificationTree/pos.redir").c_str()))) {
                                cout<<"An error occured while removing the redirect. Error code "<<ec<<"."<<endl;
                            } else {
                                if ((ec=fcopy(pth("contents.man"),"/Users/"+user+"/Library/Application Support/ClassificationTree/"+"contents.man"))) {
                                    cout<<"An error occured while moving contents. Error code "<<ec<<"."<<endl;
                                } else {
                                    if ((ec=remove(pth("contents.man").c_str()))) {
                                        cout<<"An error occured while removing contents. Error code "<<ec<<"."<<endl;
                                    }
                                    for (ll i=0;i<dir.size();i++) {
                                        if ((ec=fcopy(pth(dir[i].name+".tree"),"/Users/"+user+"/Library/Application Support/ClassificationTree/"+dir[i].name+".tree"))) {
                                            cout<<"An error occured while moving "<<dir[i].name<<". Error code "<<ec<<"."<<endl;
                                        } else {
                                            if ((ec=remove((pth(dir[i].name)+".tree").c_str()))) {
                                                cout<<"An error occured while removing "<<dir[i].name<<". Error code "<<ec<<"."<<endl;
                                            }
                                        }
                                    }
                                    if ((ec = rmdir(libpath.substr(0,libpath.length()-1).c_str()))) {
                                        cout<<"An error occured while deleting the old directory. Error code "<<ec<<"."<<endl;
                                    }
                                    libpath = "/Users/"+user+"/Library/Application Support/ClassificationTree/";
                                    cout<<"Library position successfully changed back to default."<<endl;
                                }
                            }
                        }
                    }
                } else /* Exit program */ {
                    out.open(pth("contents.man"));
                    out<<sortmode<<endl;
                    for (ll i=0;i<dir.size();i++) {
                        out<<dir[i].name<<endl<<dir[i].create<<endl<<dir[i].mod<<endl<<dir[i].size<<endl;
                    }
                    out.close();
                    return 0;
                }
            } else /* Exit program */ {
                out.open(pth("contents.man"));
                out<<sortmode<<endl;
                for (ll i=0;i<dir.size();i++) {
                    out<<dir[i].name<<endl<<dir[i].create<<endl<<dir[i].mod<<endl<<dir[i].size<<endl;
                }
                out.close();
                return 0;
            }
            if (treeop) {
                cout<<"What would you like to do with this tree?"<<endl<<"[1]View extra info"<<endl<<"[2]Run"<<endl<<"[3]Export"<<endl<<"[4]Duplicate"<<endl<<"[5]Delete"<<endl<<"[6]Rename"<<endl<<"[7]Search"<<endl<<"[8]Nothing"<<endl;
                string inp;
                while (true) {
                    getline(cin,inp);
                    if (isint(inp)) {
                        if (atoll(inp.c_str())<=8&&atoll(inp.c_str())>=1) {
                            break;
                        }
                    }
                    cout<<"Invalid answer!"<<endl;
                }
                if (inp=="1") /* Tree-Show metadata */ {
                    cout<<"Date created:"<<dir[fpoint].create<<endl;;
                    cout<<"Date modified:"<<dir[fpoint].mod<<endl;
                    cout<<"Size:"<<dir[fpoint].size<<" nodes"<<endl;
                }
                else if (inp=="2") /* Tree-Run */ {
                    tree.clear();
                    break;
                }
                else if (inp=="3") /* Tree-Export */ {
                    cout<<"What is the path of the file you would like to export to?"<<endl;
                    string epath;
                    getline(cin,epath);
                    if ((ec=fcopy(file,epath+"/"+dname+".tree"))) {
                        cout<<"A error occured while exporting the tree. Error code "<<ec<<'.'<<endl;
                    } else {
                        cout<<"Export success!"<<endl;
                    }
                }
                else if (inp=="4") /* Tree-Duplicate */ {
                    cout<<"What should the duplicate be called?"<<endl;
                    string tmp;
                    bool run = true;
                    while (run) {
                        getline(cin,tmp);
                        for (ll i=0;i<dir.size();i++) {
                            if (tmp==dir[i].name) {
                                run = false;
                                cout<<"Invalid name! Tree already exists!"<<endl;
                                break;
                            }
                        }
                        if (tmp.find(':')!=string::npos||tmp.find(';')!=string::npos) {
                            cout<<"Error! File names cannot contain : and ;."<<endl;
                            run = false;
                        }
                        if (run == true) {
                            break;
                        }
                        run = !run;
                    }
                    in.open(libpath+tmp+".tree");
                    if ((ec=fcopy(libpath+dname+".tree",libpath+tmp+".tree"))) {
                        cout<<"A error occured while duplicating the tree. Error code "<<ec<<'.'<<endl;
                    } else {
                        cout<<"Duplication successful!"<<endl;
                        dir.push_back((trfl){tmp,date(),date(),dir[fpoint].size});
                    }
                    in.close();
                }
                else if (inp=="5") /* Tree-Delete */ {
                    cout<<"Are you sure you want to delete "<<dname<<"? This action is irreversible. (Enter y or n)"<<endl;
                    string ans = ask();
                    if (ans=="y") {
                        if ((ec=remove((libpath+dname+".tree").c_str()))) {
                            cout<<"A error occured while deleting the tree. Error code "<<ec<<'.'<<endl;
                        } else {
                            cout<<"Tree deleted successfully."<<endl;
                            dir.erase(dir.begin()+fpoint);
                        }
                    }
                }
                else if (inp=="6") /* Tree-Rename */ {
                    cout<<"What would be the new name?"<<endl;
                    string tmp;
                    bool run = true;
                    while (run) {
                        getline(cin,tmp);
                        for (ll i=0;i<dir.size();i++) {
                            if (tmp==dir[i].name) {
                                run = false;
                                cout<<"Invalid name! Tree already exists!"<<endl;
                                break;
                            }
                        }
                        if (tmp.find(':')!=string::npos||tmp.find(';')!=string::npos) {
                            cout<<"Error! File names cannot contain : and ;."<<endl;
                            run = false;
                        }
                        if (run == true) {
                            break;
                        }
                        run = !run;
                    }
                    if ((ec=rename((libpath+dname+".tree").c_str(),(libpath+tmp+".tree").c_str()))) {
                        cout<<"A error occured while renaming. Error code "<<ec<<'.'<<endl;
                    } else {
                        cout<<"Tree renamed successfully."<<endl;
                        dir[fpoint].name = tmp;
                    }
                    dir[fpoint].mod = date();
                }
                else if (inp=="7") /* Tree-Search */ {
                    if (file=="") {
                        setup = true;
                    } else {
                        tree.clear();
                        cout<<"Loading tree... ";
                        in.open(file);
                        if (in.good()) {
                            getline(in,name);
                            while (!in.eof()) {
                                bool stat;
                                string data;
                                ll par;
                                ll rtn;
                                ll wan;
                                in>>stat;
                                if (!in.eof()) {
                                    getline(in,data);
                                } else {
                                    if (data!="") {
                                        cout<<"Read error! Error code DATA"<<endl;
                                    }
                                    break;
                                }
                                if (!in.eof()) {
                                    in>>par;
                                } else {
                                    cout<<"Read error! Error code PAR"<<endl;
                                    break;
                                }
                                if (!in.eof()) {
                                    in>>rtn;
                                } else {
                                    cout<<"Read error! Error code RNODE"<<endl;
                                    break;
                                }
                                if (!in.eof()) {
                                    in>>wan;
                                } else {
                                    cout<<"Read error! Error code WNODE"<<endl;
                                    break;
                                }
                                tree.push_back((node){stat,data,par,rtn,wan,static_cast<ll>(tree.size())});
                            }
                            cout<<"Load complete."<<endl;
                            cout<<"What would you like to search for?"<<endl;
                            string sph;
                            getline(cin,sph);
                            string sphlower = sph;
                            transform(sphlower.begin(),sphlower.end(),sphlower.begin(),::tolower);
                            vector<seacont>s;
                            for (ll i=0;i<tree.size();i++) { //Search data
                                string tarlower = tree[i].data;
                                string tar = tree[i].data;
                                transform(tarlower.begin(),tarlower.end(),tarlower.begin(),::tolower);
                                if (tarlower.find(sphlower)!=string::npos) {
                                    ll rel = 0;
                                    ll l = tarlower.find(sphlower);
                                    for (ll j=l;j<l+sph.size();j++) {
                                        if (tar[j]==sph[j]) {
                                            rel++;
                                        }
                                    }
                                    s.push_back((seacont){tree[i],ld(rel)/ld(sphlower.length())});
                                }
                            }
                            if (s.size()==0) {
                                cout<<"No node called '"<<sph<<"' is found."<<endl;
                            } else {
                                sort(s.begin(),s.end(),srcmp);
                                cout<<"[1]Exit"<<endl;
                                for (ll i=0;i<s.size();i++) {
                                    cout<<"["<<i+2<<"]"<<s[i].data.data<<endl;
                                }
                                string choice;
                                while (true) {
                                    getline(cin,choice);
                                    if (isint(choice)) {
                                        if (atoll(choice.c_str())>=1&&atoll(choice.c_str())<=s.size()+1) {
                                            break;
                                        }
                                    }
                                    cout<<"Invalid answer!"<<endl;
                                }
                                if (choice == "1") {
                                    continue;
                                } else {
                                    ll chosen = atoll(choice.c_str());
                                    chosen=chosen-2;
                                    node cnode = s[chosen].data;
                                    if (cnode.stat==QST) {
                                        cout<<"This is a question node."<<endl;
                                    } else {
                                        cout<<"This is an answer node."<<endl;
                                    }
                                    if (cnode.par==-1) {
                                        cout<<"This is a root node."<<endl;
                                    }
                                    if (cnode.rtn!=-1) {
                                        cout<<"If this is right:"<<tree[cnode.rtn].data<<endl;
                                    }
                                    if (cnode.wan!=-1) {
                                        cout<<"If this is wrong:"<<tree[cnode.wan].data<<endl;
                                    }
                                    vector<stc>steps;
                                    while (true) {
                                        bool rtn=false;
                                        if (tree[cnode.par].rtn==cnode.ple) {
                                            rtn = true;
                                        }
                                        steps.push_back((stc){cnode.data,rtn});
                                        if (cnode.par==-1) {
                                            break;
                                        }
                                        cnode=tree[cnode.par];
                                    }
                                    for (ll i=steps.size()-2;i>=0;i--) {
                                        cout<<"Answer ";
                                        if (steps[i].rtn) {
                                            cout<<"yes to '";
                                        } else {
                                            cout<<"no to '";
                                        }
                                        cout<<steps[i+1].data<<"'=>";
                                    }
                                    if (steps.size()!=1) {
                                        cout<<steps[0].data<<endl;
                                    }
                                }
                            }
                        } else {
                            cout<<"Error reading from file.";
                        }
                        in.close();
                    }
                }
            }
        }
        if (!setup) /* Read in tree */ {
            if (file=="") {
                setup = true;
            } else {
                cout<<"Loading tree..."<<endl;
                in.open(file);
                if (in.good()) {
                    getline(in,name);
                    while (!in.eof()) {
                        bool stat;
                        string data;
                        ll par;
                        ll rtn;
                        ll wan;
                        in>>stat;
                        if (!in.eof()) {
                            getline(in,data);
                        } else {
                            if (data!="") {
                                cout<<"Read error! Error code DATA"<<endl;
                            }
                            break;
                        }
                        if (!in.eof()) {
                            in>>par;
                        } else {
                            cout<<"Read error! Error code PAR"<<endl;
                            break;
                        }
                        if (!in.eof()) {
                            in>>rtn;
                        } else {
                            cout<<"Read error! Error code RNODE"<<endl;
                            break;
                        }
                        if (!in.eof()) {
                            in>>wan;
                        } else {
                            cout<<"Read error! Error code WNODE"<<endl;
                            break;
                        }
                        tree.push_back((node){stat,data,par,rtn,wan,static_cast<ll>(tree.size())});
                    }
                    cout<<"Load complete."<<endl;
                } else {
                    cout<<"Error reading from file.";
                    setup = true;
                }
                in.close();
            }
        }
        string qstin;
        string rti;
        string wai;
        if (setup) /* Initialize new tree */ {
            cout<<"What is the name of this tree?"<<endl;
            bool run = true;
            while (run) {
                getline(cin,name);
                for (ll i=0;i<dir.size();i++) {
                    if (name==dir[i].name) {
                        run = false;
                        cout<<"Invalid name! Tree already exists!"<<endl;
                        break;
                    }
                }
                if (name.find(':')!=string::npos||name.find(';')!=string::npos) {
                    cout<<"Error! File names cannot contain : and ;."<<endl;
                    run = false;
                }
                if (run == true) {
                    break;
                }
                run = !run;
            }
            file = pth(name)+".tree";
            dir.push_back((trfl){name,date(),date(),3});
            cout<<"What would be the first question?"<<endl;
            getline(cin,qstin);
            cout<<"If the answer to that question is yes, then what would be the answer?"<<endl;
            getline(cin,rti);
            cout<<"If the answer to that question is no, then what would be the answer?"<<endl;
            getline(cin,wai);
            tree.push_back((node){QST,qstin,-1,1,2,0});
            tree.push_back((node){ANS,rti,0,-1,-1,1});
            tree.push_back((node){ANS,wai,0,-1,-1,2});
            fpoint = dir.size()-1;
        }
        bool quit = true;
        cout<<"Running tree... Enter d to delete any question and m to modify any question or answer. ";
        while (quit) {
            cout<<"Enter ';' to exit the tree. ";
            node currentnode = tree[0];
            while (true) {
                if (currentnode.stat==ANS) /* Deal with answer node */ {
                    cout<<"Is it a(n) "<<currentnode.data<<"? (Enter y or n)"<<endl;
                    string res;
                    while (res!="y"&&res!="n"&&res!="m"&&res!=";") {
                        getline(cin,res);
                        transform(res.begin(),res.end(),res.begin(),::tolower);
                        if (res!="y"&&res!="n"&&res!="m"&&res!=";") {
                            cout<<"Invalid answer!"<<endl;
                        }
                    }
                    if (res=="y") {
                        cout<<"Classification restart."<<endl;
                        break;
                    } else if (res=="n") {
                        cout<<"What is it?"<<endl;
                        getline(cin,wai);
                        cout<<"What is a question differentiates "<<currentnode.data<<" from "<<wai<<"?"<<endl;
                        getline(cin,qstin);
                        cout<<"Is it yes or no for "<<currentnode.data<<"? (Enter y or n)"<<endl;
                        string res2 = ask();
                        node nxtc;
                        node nxtw;
                        nxtc.stat = nxtw.stat=ANS;
                        nxtc.rtn = nxtc.wan = nxtw.wan = nxtw.rtn = -1;
                        nxtc.ple = tree.size();
                        nxtc.data = wai;
                        nxtw.data = currentnode.data;
                        nxtw.ple = tree.size()+1;
                        nxtc.par = currentnode.ple;
                        nxtw.par = currentnode.ple;
                        currentnode.stat = QST;
                        currentnode.data=qstin;
                        if (res2=="y") {
                            currentnode.rtn=tree.size()+1;
                            currentnode.wan = tree.size();
                        } else {
                            currentnode.rtn=tree.size();
                            currentnode.wan = tree.size()+1;
                        }
                        tree[currentnode.ple]=currentnode;
                        tree.push_back(nxtc);
                        tree.push_back(nxtw);
                    } else if (res=="m") {
                        cout<<"What would be the new answer for this node?"<<endl;
                        string nqst;
                        getline(cin,nqst);
                        tree[currentnode.ple].data = nqst;
                        currentnode = tree[currentnode.ple];
                    } else {
                        quit = false;
                        break;
                    }
                }
                else /* Deal with question node */ {
                    cout<<currentnode.data<<" (Enter y or n)"<<endl;
                    string res3;
                    while (res3!="y"&&res3!="n"&&res3!=";"&&res3!="d"&&res3!="m") {
                        getline(cin,res3);
                        transform(res3.begin(),res3.end(),res3.begin(),::tolower);
                        if (res3!="y"&&res3!="n"&&res3!=";"&&res3!="d"&&res3!="m") {
                            cout<<"Invalid answer!"<<endl;
                        }
                    }
                    if (res3=="y") {
                        currentnode = tree[currentnode.rtn];
                    } else if (res3=="n") {
                        currentnode = tree[currentnode.wan];
                    } else if (res3=="m") {
                        cout<<"What would be the new question for this node?"<<endl;
                        string nqst;
                        getline(cin,nqst);
                        tree[currentnode.ple].data = nqst;
                        currentnode = tree[currentnode.ple];
                    } else if (res3=="d") {
                        cout<<"Are you sure you want to delete this node? All nodes below will be removed. (Enter y or n)"<<endl;
                        string ans = ask();
                        if (ans=="y") {
                            cout<<"Deleting node... The question node will now be an answer node called 'deleted node'."<<endl;
                            tree.push_back((node){ANS,"deleted node",currentnode.par,-1,-1,static_cast<ll>(tree.size())});
                            if (currentnode.ple==tree[currentnode.par].rtn) {
                                tree[currentnode.par].rtn = tree.size()-1;
                            } else {
                                tree[currentnode.par].wan = tree.size()-1;
                            }
                            vector<ll>tbd;
                            dfs(currentnode.ple,tbd);
                            sort(tbd.begin(),tbd.end(),cmp); //Erase accordingly to tbd[i]
                            for (ll i=0;i<tbd.size();i++) {
                                tree.erase(tree.begin()+tbd[i]);
                                for (ll j=0;j<tree.size();j++) { //Messed up:RTN,WAN,PLE,PAR
                                    if (tree[j].rtn>tbd[i]) {
                                        tree[j].rtn--;
                                    }
                                    if (tree[j].wan>tbd[i]) {
                                        tree[j].wan--;
                                    }
                                    if (tree[j].par>tbd[i]) {
                                        tree[j].par--;
                                    }
                                }
                            }
                            for (ll i=0;i<tree.size();i++) {
                                tree[i].ple=i;
                            }
                            currentnode = tree[tree[tree.size()-1].par];
                            cout<<"Node deleted successfully."<<endl;
                        }
                    } else {
                        quit = false;
                        break;
                    }
                }
            }
        }
        cout<<"Saving to file..."<<endl;
        dir[fpoint].size=tree.size();
        dir[fpoint].mod=date();
        out.open(file);
        out<<name<<endl;
        for (ll i=0;i<tree.size();i++) {
            out<<tree[i].stat<<tree[i].data<<endl<<tree[i].par<<' '<<tree[i].rtn<<' '<<tree[i].wan<<endl;
        }
        cout<<"Complete."<<endl;
        out.close();
    }
    return 0;
}

/*
 Add folders!
 Search trees! (Right above Settings) Also add option for searching for tree contents also.
 */
