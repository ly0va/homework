#include <string>
#define NAME_LENGTH 50
#define CAPPED_NAME_LENGTH 46
#define DATE_LENGTH 10
#define DEFAULT_PARK 'N'
#define TOTAL_PARKS 6
#define MAX_YEAR 9999
#define MAX_MONTH 12
#define MAX_DAY 31

class DisneyCharacter {
    private:
        std::string name;
        std::string creationDate;
        int numMovies;
        char whichPark;
    public:
        DisneyCharacter(std::string name, std::string creationDate, 
                        int numMovies, char whichPark);
        DisneyCharacter(std::string name, std::string creationDate);
        ~DisneyCharacter();
        std::string GetName();
        std::string GetCreationDate();
        int GetNumMovies();
        char GetPark();
        bool SetNumMovies(int numMovies);
        bool SetPark(char whichPark);
        void ShowInfo();
        bool PlaceCharacter(char whichPark);
        void SameMovies(DisneyCharacter& anotherCharacter);
};