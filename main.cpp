#include"location.crud.cpp"
#include"diseases.crud.cpp"
#include<set>
string Stringtolower(string str){
    for(int i = 0; i < str.length(); i++){
        str[i] = tolower(str[i]);
    }
    return str;
}
enum userCommands {
    add_,
    record_,
    list_,
    where,
    cases,
    help,
    exit_,
    delete_,
    diseases,
    invalidCommand,
    max_
};
userCommands hashIt(string command){
    if(command == "add"){
        return add_;
    }
    else if(command == "record"){
        return record_;
    }
    else if(command == "list"){
        return list_;
    }
    else if(command == "where"){
        return where;
    }
    else if(command == "cases"){
        return cases;
    }
    else if(command == "help"){
        return help;
    }
    else if(command == "exit"){
        return exit_;
    }
    else if(command == "delete"){
        return delete_;
    }
    else if(command == "diseases"){
        return diseases;
    }
     else if(command == "max"){
        return max_;
    }
    else{
        return invalidCommand;
    }
}
void add( string name){
  
    Location location = getLocation(name);
    
    if(location.getName() == ""){
          vector<Location> locations = getAllLocations();
          Location newlocation;
          newlocation.setName(Stringtolower(name));
          newlocation.setId((rand()%600)+locations.size());
            addLocation(newlocation);
        return;
    }
    else{
        cout << "Location :" << name<<" already exists" << endl;
        return;
    }
    
}
void HighRankingDiseaseInLocation(string name){
    Location location = getLocation(name);
    if(location.getName() == ""){
        cout << "Location :" << name<<" does not exist" << endl;
        return;
    }
    else{
        vector<Disease> diseases = getDiseaseBylocation_id(location.getId());
        int max = 0;
        string disease_name =""; 
        for(int i = 0; i < diseases.size(); i++){
            if(diseases[i].getTotal() > max){
                max = diseases[i].getTotal();
                disease_name = diseases[i].getName();
            }
        }
        cout << "Disease :" << disease_name<<" has the most cases  " << max << " in "<<name << endl;
        return;
    }
}

void remove(string name){
    Location location = getLocation(name);
    if(location.getName() == ""){
        cout << "Location" << name<<" does not exist" << endl;
        return;
    }
    else{
        vector<Disease> diseases =getDiseaseBylocation_id(location.getId());
        for(const auto& disease : diseases){
            DeleteDisease(disease);
        }
        removeLocation(name);
        return;
    }
}
void DiseasesInLocation(string name){
    Location location = getLocation(name);
    if(location.getName() == ""){
        cout << "Location :" << name<<" does not exist" << endl;
        return;
    }
    else{
        vector<Disease> diseases =getDiseaseBylocation_id(location.getId());
        for( auto& disease : diseases){
            cout << disease.getName() << endl;
        }
        return;
    }
}
 void record(string locationName , string disease_name , int total){
    Location location = getLocation(Stringtolower(locationName));
    if(location.getName() == ""){
        cout << "Location: " << locationName<<" does not exist" << endl;
        return;
    }
    else{
        Disease disease = getDiseaseBylocation_idAndName(location.getId(),Stringtolower(disease_name));
        if(disease.getName() == ""){
          Disease newdisease;
          newdisease.setName(Stringtolower(disease_name));
          newdisease.setTotal(total);
          newdisease.setLocation_id(location.getId());
          addDisease(newdisease);
            return;
        }
        else{
            disease.setTotal(disease.getTotal() + total);
            UpdateDisease(disease);
            return;
        }
    }

 }
 void casesInLocation(string locationName , string disease_name){
    Location location = getLocation(Stringtolower(locationName));
    if(location.getName() == ""){
        cout << "Location:" << locationName<<" does not exist" << endl;
        return;
    }
    else{
        Disease disease = getDiseaseBylocation_idAndName(location.getId(),Stringtolower(disease_name));
        if(disease.getName() == ""){
            cout << "Disease " << disease_name<<" has: "<<0 << " cases in: " << locationName<<endl;
            return;
        }
        else{
            cout << "Disease " << disease_name<<" has: " << disease.getTotal() << " cases in: " << locationName << endl;
            return;
        }
    }
 }
   void casesOfDisease(string disease_name){
    vector<Location> locations = getAllLocations();
    vector<Disease> diseases = getAllDiseasesByName(Stringtolower(disease_name));
    int total = 0;
    if (diseases.size() == 0)
    {
        cout << "Disease" << disease_name<<" does not exist" << endl;
        return;
    }
    else
    {
      for( auto& disease : diseases){
        total=total+disease.getTotal();
     }
        cout<<"Total cases Of '"<<disease_name<<"'="<<total<< endl;
        return;
    }
    
     
     
   }
   void list(string command){
    if(command == "locations"){
        vector<Location> unSortedlocations = getAllLocations();
        vector<Location> locations = mergeSortByname(unSortedlocations);
        if(locations.size() == 0){
            cout << "No locations found" << endl;
            return;
        }
        else{
            for( auto& location : locations){
                cout << location.getName() << endl;
            }
            return;
        }
    }
    else if(command == "diseases"){
        vector<Disease> diseases = mergeSortDiseaseByname(getAllDiseases());
        set<string> diseaseNames;
        if(diseases.size() == 0){
            cout << "No diseases found" << endl;
            return;
        }
        else{
            for(int i = 0; i < diseases.size(); i++){
                diseaseNames.insert(diseases[i].getName());
            }
            for(const auto& diseaseName : diseaseNames){
                cout << diseaseName << endl;
            }
        }
        
    }
    
   }
   void WhereDisease(string disease_name){
    vector<Location> locations = getAllLocations();
    vector<Disease> diseases = getAllDiseasesByName(Stringtolower(disease_name));
    int total = 0;
    if (diseases.size() == 0){
        cout << "Disease " << disease_name<<" does not exist" << endl;
        return;
    }
    else{
    for(auto& disease : diseases){
         for(auto& location : locations){
             if(disease.getLocation_id() == location.getId()){
                cout << location.getName() << endl;
         }
     }
    }
     
     }
     }
      
void displayMenu(){
        cout << "========================================================================="<<endl;
        cout << "*                             HELP  MENU                                *"<<endl;
        cout << "========================================================================="<<endl;
        cout << "add<location>                          :Add a new location               "<<endl;
        cout << "delete<location>                       :Delete an existing location      "<<endl;
        cout << "record <Location> <disease>  <cases>   :Record a new case of disease     "<<endl;
        cout << "list locations                         :List existing all locations      "<<endl;
        cout << "list diseases                          :List existing all locations      "<<endl;
        cout << "where <disease>                        :where disease exists             "<<endl;
        cout << "cases <location> <disease>             :find cases of disease in location"<<endl;
        cout << "cases <disease>                        :find total cases of disease      "<<endl;
        cout << "diseases<location>                    :find total cases of disease       "<<endl;                 
        cout << "help                                   :Display this help menu           "<<endl;
        cout << "exit                                   :Exit the program                 "<<endl;
}
void  WelcomeMenu(){
    string help;
    cout <<"==========================================================="<<endl;
    cout <<"* Welcome to Disease Cases Reporting System               *"<<endl;
    cout <<"*                                                         *"<<endl;
    cout <<"* It is developed by 'Cyusa Munezero Keny' as practical   *"<<endl;
    cout <<"* evaluation for the 3rd year                             *"<<endl;
    cout <<"==========================================================="<<endl;
    cout <<""<<endl;   
    cout <<"Starting Time : Thu Apr 05 23:59:08 CAT 2022   "<<endl;
    cout <<"Need a help ? Type help then press enter key else"<<endl;
    cout <<"Console > ";
    getline(cin,help);
    help = Stringtolower(help);
    if(help == "help"){
     displayMenu();
    }
    else if(help == "exit"){
        cout <<"Exiting the program"<<endl;
        exit(0);
    }
    else{
        cout <<"Starting the program"<<endl;
    }
}
int main(){
    WelcomeMenu();
    string fullcommand;
    string command;
    string inputText; 
    AppInput:cout << "Console > ";
    getline(cin,fullcommand);
    command = fullcommand.substr(0,fullcommand.find(" "));
    inputText = fullcommand.substr(fullcommand.find(" ")+1);
    switch(hashIt(Stringtolower(command))){
        case add_:{
            add(Stringtolower(inputText));
            goto AppInput;
        }
            
        case delete_:{
            remove(Stringtolower(inputText));
            goto AppInput;
        }
           
        case record_:{
            int end = inputText.find(" ");
            string locationName =inputText.substr(0,end);
            inputText.erase(0,end+1);
            end = inputText.find(" ");
            string diseaseName = inputText.substr(0,end);
            inputText.erase(0,end+1);
            end = inputText.find(" ");
            int cases = stoi(inputText);
            record(Stringtolower(locationName),Stringtolower(diseaseName),cases);
        }
        case list_:{
            list(Stringtolower(inputText));
            goto AppInput;
        }
        case where:{
            WhereDisease(Stringtolower(inputText));
            goto AppInput;
        }
            
        case cases:{
        int end2 = inputText.find(" ");
            int end = inputText.find(" ");
            int nbrOfinputs = inputText.find(" ");
            string input1 =inputText.substr(0,end);
            inputText.erase(0,end+1);
            end = inputText.find(" ");
            string input2 = inputText.substr(0,end);
            if(nbrOfinputs==-1){
               casesOfDisease(input1);
            }
            else{
               casesInLocation(input1,input2);
            }
            goto AppInput;
            exit(0);
        }
        case exit_:{
            cout <<"Exiting the program"<<endl;
            exit(0);
        }
        case help:{
            displayMenu();
            goto AppInput;
        }
        case diseases:{
            DiseasesInLocation(Stringtolower(inputText));
            goto AppInput;
        }
        case max_:{
            int end = inputText.find(" ");
            string requestType =inputText.substr(0,end);
            inputText.erase(0,end+1);
            end = inputText.find(" ");
            string data = inputText.substr(0,end);
            if(requestType=="location"){
                HighRankingDiseaseInLocation(Stringtolower(data));
            }
            else{
                cout <<"Invalid request type"<<endl;
            }
            goto AppInput;
        }
            
        default:{
            cout <<"Invalid command type 'help' to view commands"<<endl;
            goto AppInput;
        }
    }
    return 0;
}