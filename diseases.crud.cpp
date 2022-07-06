#include"diseases.cpp"
#include<fstream>
#include<vector>
using namespace std;
// Actions on a disease
void addDisease(Disease disease){
    ofstream file;
    file.open("disease.txt", ios::app);
    file << disease.getName() <<"|"<< disease.getTotal() <<"|"<< disease.getLocation_id() <<"\n"<< endl;
    file.close();
}
Disease changeFromStringtoDisease(string line){
    Disease disease;
    size_t pos = line.find("|");
    string item;
    int i = 0;
    while(pos != string::npos){
        item = line.substr(0, pos);
        if(i == 0){
            disease.setName(item);
        }
        else if(i == 1){
            disease.setTotal(stoi(item));
        }

        line.erase(0, pos + 1);
        pos = line.find("|");
        i++;
        }
        disease.setLocation_id(stoi(line));
    return disease;
}
vector<Disease> getAllDiseases(){
    vector<Disease> diseases;
    ifstream file;
    file.open("disease.txt");
    string line;
    while(getline(file, line)){
        if (line.length() != 0){
            diseases.push_back(changeFromStringtoDisease(line));
        }
        {
            continue;
        }
        
    }
    file.close();
    return diseases;
}
vector<Disease>getDiseaseBylocation_id(int id){
    vector<Disease> diseases = getAllDiseases();
    vector<Disease> diseases_by_location_id;
    for(int i = 0; i < diseases.size(); i++){
        if(diseases[i].getLocation_id() == id){
            diseases_by_location_id.push_back(diseases[i]);
        }
    }
    return diseases_by_location_id;
}
vector<Disease> getAllDiseasesByName(string name){
    vector<Disease> diseases = getAllDiseases();
    vector<Disease> diseasesByName;
    for(int i = 0; i < diseases.size(); i++){
        if(diseases[i].getName() == name){
            diseasesByName.push_back(diseases[i]);
        }
    }
    return diseasesByName;
}
void removeDiseases(string disease_name){
    vector<Disease> diseases = getAllDiseases();
    ofstream file;
    file.open("disease.txt");
    for(int i = 0; i < diseases.size(); i++){
        if(diseases[i].getName() != disease_name){
            file << diseases[i].getName() <<"|"<< diseases[i].getTotal() <<"|"<< diseases[i].getLocation_id() <<"\n"<< endl;
        }
    }
    file.close();
}
Disease getDiseaseBylocation_idAndName(int location_id, string disease_name){
    vector<Disease> diseases = getAllDiseases();
    for(int i = 0; i < diseases.size(); i++){
        if(diseases[i].getLocation_id() == location_id && diseases[i].getName() == disease_name){
            return diseases[i];
        }
    }
    return Disease();
    }
void UpdateDisease(Disease disease){
    vector<Disease> diseases = getAllDiseases();
    ofstream file;
    file.open("disease.txt");
    for(int i = 0; i < diseases.size(); i++){
        if(diseases[i].getName() == disease.getName() && diseases[i].getLocation_id() == disease.getLocation_id()){
            file << disease.getName() <<"|"<< disease.getTotal() <<"|"<< disease.getLocation_id() <<"\n"<< endl;
        }
        else{
            file << diseases[i].getName() <<"|"<< diseases[i].getTotal() <<"|"<< diseases[i].getLocation_id() <<"\n"<< endl;
        }
    }
    file.close();
}
void DeleteDisease(Disease disease){
    vector<Disease> diseases = getAllDiseases();
    ofstream file;
    file.open("disease.txt");
    for(int i = 0; i < diseases.size(); i++){
        if(diseases[i].getName() != disease.getName() || diseases[i].getLocation_id() != disease.getLocation_id()){
            file << diseases[i].getName() <<"|"<< diseases[i].getTotal() <<"|"<< diseases[i].getLocation_id() <<"\n"<< endl;
        }
    }
    file.close();
}
vector<Disease> mergeDisease(vector<Disease> left, vector<Disease> right){
    vector<Disease> merged;
    while(left.size() != 0 && right.size() != 0){
        if(left[0].getName() < right[0].getName()){
            merged.push_back(left[0]);
            left.erase(left.begin());
        }
        else{
            merged.push_back(right[0]);
            right.erase(right.begin());
        }
    }
    while(left.size() != 0){
        merged.push_back(left[0]);
        left.erase(left.begin());
    }
    while(right.size() != 0){
        merged.push_back(right[0]);
        right.erase(right.begin());
    }
    return merged;
}

vector<Disease>mergeSortDiseaseByname(vector<Disease> locations){
    if(locations.size() <= 1){
        return locations;
    }
    int mid = locations.size()/2;
    vector<Disease> left = mergeSortDiseaseByname(vector<Disease>(locations.begin(), locations.begin() + mid));
    vector<Disease> right = mergeSortDiseaseByname(vector<Disease>(locations.begin() + mid, locations.end()));
    vector<Disease> merged = mergeDisease(left, right);
    return merged;
}
