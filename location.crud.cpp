#include"location.cpp"
#include<fstream>
#include<vector>
using namespace std;
// Actions on a location
void addLocation(Location location){
    ofstream file;
    file.open("location.txt", ios::app);
    file << location.getId() <<"|"<< location.getName() <<"\n"<< endl;
    file.close();
}
Location changeStringToLocation(string line){
    Location location;
    size_t pos = line.find("|");
    string item;
    int i = 0;
   while(pos != string::npos){
       item = line.substr(0, pos);
       if(i == 0){
           location.setId(stoi(item));
       }
    
       line.erase(0, pos + 1);
       pos = line.find("|");
       i++;
       }
        location.setName(line);
    return location;
}
vector<Location> getAllLocations(){
    vector<Location> locations;
    ifstream file;
    file.open("location.txt");
    string line;
    while(getline(file, line)){
        if (line.length() != 0){
            locations.push_back(changeStringToLocation(line));
        }
        {
            continue;
        }
        
    }
    file.close();
    return locations;
}
Location getLocation(string name){
  vector<Location> locations = getAllLocations();
  for(int i = 0; i < locations.size(); i++){
      if(locations[i].getName() == name){
          return locations[i];
      }
  }
  return Location();
}
void removeLocation(string name){
    vector<Location> locations = getAllLocations();
    ofstream file;
    file.open("location.txt");
    for(int i = 0; i < locations.size(); i++){
        if(locations[i].getName() != name){
            file << locations[i].getId() <<"|"<< locations[i].getName() <<"\n"<< endl;
        }
    }
    file.close();
}

vector<Location> merge(vector<Location> left, vector<Location> right){
    vector<Location> merged;
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

vector<Location>mergeSortByname(vector<Location> locations){
    if(locations.size() <= 1){
        return locations;
    }
    int mid = locations.size()/2;
    vector<Location> left = mergeSortByname(vector<Location>(locations.begin(), locations.begin() + mid));
    vector<Location> right = mergeSortByname(vector<Location>(locations.begin() + mid, locations.end()));
    vector<Location> merged = merge(left, right);
    return merged;
}


