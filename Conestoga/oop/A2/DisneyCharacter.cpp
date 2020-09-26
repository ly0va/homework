#include "DisneyCharacter.h"
#include <stdio.h>
#include <string.h>
#include <string>

DisneyCharacter::DisneyCharacter(std::string name, std::string creationDate, 
                                 int numMovies, char whichPark) {
    int year = 0;
    int month = 0;
    int day = 0;

    if (name.size() > NAME_LENGTH) {
        this->name = name.substr(0, CAPPED_NAME_LENGTH);
        this->name += " ...";
    } else {
        this->name = name;
    }

    if (creationDate.size() != DATE_LENGTH ||
        sscanf(creationDate.c_str(), "%d-%d-%d", &year, &month, &day) != 3 || 
        year < 1 || month < 1 || day < 1 || 
        year > MAX_YEAR || month > MAX_MONTH || day > MAX_DAY) {
            this->creationDate = "";
    } else {
        this->creationDate = creationDate;
    }

    this->numMovies = numMovies >= 0 ? numMovies : 0;

    bool validPark = strchr("MSAECN", whichPark) != NULL;
    this->whichPark = validPark ? whichPark : DEFAULT_PARK;
}

DisneyCharacter::DisneyCharacter(std::string name, std::string creationDate) {
    int year = 0;
    int month = 0;
    int day = 0;

    if (name.size() > NAME_LENGTH) {
        this->name = name.substr(0, CAPPED_NAME_LENGTH);
        this->name += " ...";
    } else {
        this->name = name;
    }

    if (creationDate.size() != DATE_LENGTH ||
        sscanf(creationDate.c_str(), "%d-%d-%d", &year, &month, &day) != 3 || 
        year < 1 || month < 1 || day < 1 || 
        year > MAX_YEAR || month > MAX_MONTH || day > MAX_DAY) {
            this->creationDate = "";
    } else {
        this->creationDate = creationDate;
    }

    this->numMovies = 0;
    this->whichPark = DEFAULT_PARK;
}

DisneyCharacter::~DisneyCharacter() {
    printf("%s destroyed.\n", name.c_str());
}

std::string DisneyCharacter::GetName() {
    return name;
}

std::string DisneyCharacter::GetCreationDate() {
    return creationDate;
}

int DisneyCharacter::GetNumMovies() {
    return numMovies;
}

char DisneyCharacter::GetPark() {
    return whichPark;
}

bool DisneyCharacter::SetNumMovies(int numMovies) {
    bool valid = numMovies >= 0;
    this->numMovies = valid ? numMovies : this->numMovies;
    return valid;
}

bool DisneyCharacter::SetPark(char whichPark) {
    bool valid = strchr("MSAECN", whichPark) != NULL;
    this->whichPark = valid ? whichPark : this->whichPark;
    return valid;
}

bool DisneyCharacter::PlaceCharacter(char whichPark) {
    bool valid = strchr("MSAECN", whichPark) != NULL;
    this->whichPark = valid ? whichPark : this->whichPark;
    return valid;
}

void DisneyCharacter::ShowInfo() {
    char parkCodes[TOTAL_PARKS+1] = "MSAECN";
    std::string parks[TOTAL_PARKS] = {"Magic Kingdom.", 
                                      "Disney Studios.", 
                                      "Animal Kingdom.",
                                      "Epcot.", 
                                      "California Adventure.",
                                      "N/A"};
    std::string park;
    for (int i = 0; i < TOTAL_PARKS; i++) {
        if (whichPark == parkCodes[i]) {
            park = parks[i];
        }
    }
    printf("Character's name is:       %s\n"
           "It was created in:         %s\n"
           "# of movies featured in:   %d\n"
           "You can find it in:        %s\n\n", 
           name.c_str(), creationDate.c_str(), numMovies, park.c_str());
}

void DisneyCharacter::SameMovies(DisneyCharacter& anotherCharacter) {
    numMovies = anotherCharacter.numMovies; 
}
