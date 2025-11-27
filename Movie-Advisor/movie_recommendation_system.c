#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <windows.h>
#include <ctype.h>

// Define constants
#define MAX_USERS 100
#define MAX_MOVIES 1000
#define MAX_USER_MOVIES 100
#define NAME_LENGTH 50
#define MOVIE_TITLE_LENGTH 100

// Structure to store user information
struct User {
    char name[NAME_LENGTH];
    char watched_movies[MAX_USER_MOVIES][MOVIE_TITLE_LENGTH];
    int movie_count;
};

// Structure to store movie information
struct Movie {
    char title[MOVIE_TITLE_LENGTH];
    char genre[50];
    char director[50];
    int year;
};

// Global arrays to store data
struct User users[MAX_USERS];
struct Movie movies[MAX_MOVIES];
int user_count = 0;
int movie_count = 0;

// Function to compare strings ignoring case
int string_compare_ignore_case(char* str1, char* str2);

// Function declarations
void load_default_movies();
void load_user_data();
void save_user_data(int user_index);
int find_user(char* name);
int register_user(char* name);
int find_movie(char* title);
void recommend_movies(char* user_name, char* movie_title);
int get_similarity_score(char* movie1, char* movie2);
void display_user_history(char* user_name);
void clear_screen();

int main() {
    char user_name[NAME_LENGTH];
    char movie_title[MOVIE_TITLE_LENGTH];
    int choice;
    int user_index;
    
    // Load default movies and user data
    load_default_movies();
    load_user_data();
    
    printf("=== Welcome to Movie Advisor System ===\n");
    printf("Please enter your name to login: ");
    fgets(user_name, sizeof(user_name), stdin);
    // Remove newline character
    user_name[strcspn(user_name, "\n")] = 0;
    
    // Check if user exists or register new user
    user_index = find_user(user_name);
    if (user_index == -1) {
        user_index = register_user(user_name);
        printf("New user registered: %s\n", user_name);
    } else {
        printf("Welcome back, %s!\n", user_name);
        display_user_history(user_name);
    }
    
    while(1) {
        printf("\n(: Movie Recommendation System :)\n");
        printf("1. Search for a movie and get recommendations\n");
        printf("2. View your movie history\n");
        printf("3. Press ESC to exit\n");
        
        choice = _getch(); // Get user input without pressing Enter
        
        if (choice == 27) { // ESC key
            printf("\nThank you for using Movie Advisor System!\n");
            break;
        }
        
        switch(choice) {
            case '1':
                printf("\nEnter movie name: ");
                fgets(movie_title, sizeof(movie_title), stdin);
                // Remove newline character
                movie_title[strcspn(movie_title, "\n")] = 0;
                
                if (find_movie(movie_title) != -1) {
                    recommend_movies(user_name, movie_title);
                } else {
                    printf("Sorry, we don't have information about '%s' in our database.\n", movie_title);
                }
                break;
                
            case '2':
                display_user_history(user_name);
                break;
                
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    }
    
    return 0;
}

// Function to compare two strings ignoring case
int string_compare_ignore_case(char* str1, char* str2) {
    int i = 0;
    
    // Convert both strings to lowercase for comparison
    while (str1[i] && str2[i]) {
        if (tolower(str1[i]) != tolower(str2[i])) {
            return 0; // Not equal
        }
        i++;
    }
    
    // Check if both strings ended at the same position
    if (str1[i] == '\0' && str2[i] == '\0') {
        return 1; // Equal
    }
    
    return 0; // Not equal
}

// Function to load default movies into the system
void load_default_movies() {
    // Action movies
    strcpy(movies[movie_count].title, "The Dark Knight");
    strcpy(movies[movie_count].genre, "Action");
    strcpy(movies[movie_count].director, "Christopher Nolan");
    movies[movie_count].year = 2008;
    movie_count++;
    
    strcpy(movies[movie_count].title, "Avengers: Endgame");
    strcpy(movies[movie_count].genre, "Action");
    strcpy(movies[movie_count].director, "Russo Brothers");
    movies[movie_count].year = 2019;
    movie_count++;
    
    strcpy(movies[movie_count].title, "Mad Max: Fury Road");
    strcpy(movies[movie_count].genre, "Action");
    strcpy(movies[movie_count].director, "George Miller");
    movies[movie_count].year = 2015;
    movie_count++;
    
    strcpy(movies[movie_count].title, "John Wick");
    strcpy(movies[movie_count].genre, "Action");
    strcpy(movies[movie_count].director, "Chad Stahelski");
    movies[movie_count].year = 2014;
    movie_count++;
    
    strcpy(movies[movie_count].title, "Die Hard");
    strcpy(movies[movie_count].genre, "Action");
    strcpy(movies[movie_count].director, "John McTiernan");
    movies[movie_count].year = 1988;
    movie_count++;
    
    // Comedy movies
    strcpy(movies[movie_count].title, "The Grand Budapest Hotel");
    strcpy(movies[movie_count].genre, "Comedy");
    strcpy(movies[movie_count].director, "Wes Anderson");
    movies[movie_count].year = 2014;
    movie_count++;
    
    strcpy(movies[movie_count].title, "Superbad");
    strcpy(movies[movie_count].genre, "Comedy");
    strcpy(movies[movie_count].director, "Greg Mottola");
    movies[movie_count].year = 2007;
    movie_count++;
    
    strcpy(movies[movie_count].title, "Anchorman: The Legend of Ron Burgundy");
    strcpy(movies[movie_count].genre, "Comedy");
    strcpy(movies[movie_count].director, "Adam McKay");
    movies[movie_count].year = 2004;
    movie_count++;
    
    strcpy(movies[movie_count].title, "Bridesmaids");
    strcpy(movies[movie_count].genre, "Comedy");
    strcpy(movies[movie_count].director, "Paul Feig");
    movies[movie_count].year = 2011;
    movie_count++;
    
    strcpy(movies[movie_count].title, "Groundhog Day");
    strcpy(movies[movie_count].genre, "Comedy");
    strcpy(movies[movie_count].director, "Harold Ramis");
    movies[movie_count].year = 1993;
    movie_count++;
    
    // Drama movies
    strcpy(movies[movie_count].title, "The Shawshank Redemption");
    strcpy(movies[movie_count].genre, "Drama");
    strcpy(movies[movie_count].director, "Frank Darabont");
    movies[movie_count].year = 1994;
    movie_count++;
    
    strcpy(movies[movie_count].title, "Forrest Gump");
    strcpy(movies[movie_count].genre, "Drama");
    strcpy(movies[movie_count].director, "Robert Zemeckis");
    movies[movie_count].year = 1994;
    movie_count++;
    
    strcpy(movies[movie_count].title, "The Godfather");
    strcpy(movies[movie_count].genre, "Drama");
    strcpy(movies[movie_count].director, "Francis Ford Coppola");
    movies[movie_count].year = 1972;
    movie_count++;
    
    strcpy(movies[movie_count].title, "Pulp Fiction");
    strcpy(movies[movie_count].genre, "Drama");
    strcpy(movies[movie_count].director, "Quentin Tarantino");
    movies[movie_count].year = 1994;
    movie_count++;
    
    strcpy(movies[movie_count].title, "Fight Club");
    strcpy(movies[movie_count].genre, "Drama");
    strcpy(movies[movie_count].director, "David Fincher");
    movies[movie_count].year = 1999;
    movie_count++;
    
    // Sci-Fi movies
    strcpy(movies[movie_count].title, "Interstellar");
    strcpy(movies[movie_count].genre, "Sci-Fi");
    strcpy(movies[movie_count].director, "Christopher Nolan");
    movies[movie_count].year = 2014;
    movie_count++;
    
    strcpy(movies[movie_count].title, "Blade Runner 2049");
    strcpy(movies[movie_count].genre, "Sci-Fi");
    strcpy(movies[movie_count].director, "Denis Villeneuve");
    movies[movie_count].year = 2017;
    movie_count++;
    
    strcpy(movies[movie_count].title, "The Matrix");
    strcpy(movies[movie_count].genre, "Sci-Fi");
    strcpy(movies[movie_count].director, "Wachowski Sisters");
    movies[movie_count].year = 1999;
    movie_count++;
    
    strcpy(movies[movie_count].title, "Arrival");
    strcpy(movies[movie_count].genre, "Sci-Fi");
    strcpy(movies[movie_count].director, "Denis Villeneuve");
    movies[movie_count].year = 2016;
    movie_count++;
    
    strcpy(movies[movie_count].title, "Ex Machina");
    strcpy(movies[movie_count].genre, "Sci-Fi");
    strcpy(movies[movie_count].director, "Alex Garland");
    movies[movie_count].year = 2014;
    movie_count++;
    
    // Horror movies
    strcpy(movies[movie_count].title, "Get Out");
    strcpy(movies[movie_count].genre, "Horror");
    strcpy(movies[movie_count].director, "Jordan Peele");
    movies[movie_count].year = 2017;
    movie_count++;
    
    strcpy(movies[movie_count].title, "Hereditary");
    strcpy(movies[movie_count].genre, "Horror");
    strcpy(movies[movie_count].director, "Ari Aster");
    movies[movie_count].year = 2018;
    movie_count++;
    
    strcpy(movies[movie_count].title, "The Babadook");
    strcpy(movies[movie_count].genre, "Horror");
    strcpy(movies[movie_count].director, "Jennifer Kent");
    movies[movie_count].year = 2014;
    movie_count++;
    
    strcpy(movies[movie_count].title, "A Quiet Place");
    strcpy(movies[movie_count].genre, "Horror");
    strcpy(movies[movie_count].director, "John Krasinski");
    movies[movie_count].year = 2018;
    movie_count++;
    
    strcpy(movies[movie_count].title, "The Conjuring");
    strcpy(movies[movie_count].genre, "Horror");
    strcpy(movies[movie_count].director, "James Wan");
    movies[movie_count].year = 2013;
    movie_count++;
}

// Function to load user data from file
void load_user_data() {
    FILE *file;
    char filename[NAME_LENGTH + 20];
    int i, j;
    
    // Try to load each potential user file
    for (i = 0; i < MAX_USERS; i++) {
        sprintf(filename, "database\\user_%d.txt", i);
        file = fopen(filename, "r");
        if (file != NULL) {
            // Read user name
            if (fscanf(file, "%s\n", users[user_count].name) == 1) {
                // Read number of movies
                fscanf(file, "%d\n", &users[user_count].movie_count);
                
                // Read each movie
                for (j = 0; j < users[user_count].movie_count && j < MAX_USER_MOVIES; j++) {
                    fscanf(file, "%s\n", users[user_count].watched_movies[j]);
                }
                
                user_count++;
            }
            fclose(file);
        }
    }
}

// Function to save user data to file
void save_user_data(int user_index) {
    FILE *file;
    char filename[NAME_LENGTH + 20];
    int i;
    
    sprintf(filename, "database\\user_%d.txt", user_index);
    file = fopen(filename, "w");
    
    if (file != NULL) {
        fprintf(file, "%s\n", users[user_index].name);
        fprintf(file, "%d\n", users[user_index].movie_count);
        
        for (i = 0; i < users[user_index].movie_count; i++) {
            fprintf(file, "%s\n", users[user_index].watched_movies[i]);
        }
        
        fclose(file);
    }
}

// Function to find a user by name
int find_user(char* name) {
    int i;
    for (i = 0; i < user_count; i++) {
        if (strcmp(users[i].name, name) == 0) {
            return i;
        }
    }
    return -1;
}

// Function to register a new user
int register_user(char* name) {
    if (user_count < MAX_USERS) {
        strcpy(users[user_count].name, name);
        users[user_count].movie_count = 0;
        return user_count++;
    }
    return -1; // User limit reached
}

// Function to find a movie by title
int find_movie(char* title) {
    int i;
    for (i = 0; i < movie_count; i++) {
        if (string_compare_ignore_case(movies[i].title, title) == 1) {
            return i;
        }
    }
    return -1;
}

// Function to add a movie to user's history
void add_movie_to_history(char* user_name, char* movie_title) {
    int user_index = find_user(user_name);
    
    if (user_index != -1) {
        if (users[user_index].movie_count < MAX_USER_MOVIES) {
            strcpy(users[user_index].watched_movies[users[user_index].movie_count], movie_title);
            users[user_index].movie_count++;
            save_user_data(user_index);
        }
    }
}

// Function to calculate similarity between two movies
int get_similarity_score(char* movie1, char* movie2) {
    int i, j;
    int movie1_idx = find_movie(movie1);
    int movie2_idx = find_movie(movie2);
    
    if (movie1_idx == -1 || movie2_idx == -1) {
        return 0;
    }
    
    int score = 0;
    
    // Compare genres
    if (strcmp(movies[movie1_idx].genre, movies[movie2_idx].genre) == 0) {
        score += 50; // High similarity for same genre
    }
    
    // Compare directors (bonus points if same director)
    if (strcmp(movies[movie1_idx].director, movies[movie2_idx].director) == 0) {
        score += 30; // Additional points for same director
    }
    
    // Compare release years (closer years = more similar)
    int year_diff = abs(movies[movie1_idx].year - movies[movie2_idx].year);
    if (year_diff <= 5) {
        score += 20 - (year_diff * 2); // More points for closer years
    }
    
    return score;
}

// Function to recommend movies based on user's selected movie
void recommend_movies(char* user_name, char* movie_title) {
    int i, j;
    int similarity_scores[MAX_MOVIES];
    int temp_movie_indices[MAX_MOVIES];
    char temp_movie_titles[MAX_MOVIES][MOVIE_TITLE_LENGTH];
    int movie_added = 0;
    
    printf("\nSearching for movies similar to '%s'...\n\n", movie_title);
    
    // Calculate similarity scores for all movies
    for (i = 0; i < movie_count; i++) {
        // Skip the movie the user searched for
        if (string_compare_ignore_case(movies[i].title, movie_title) == 0) {
            similarity_scores[movie_added] = get_similarity_score(movie_title, movies[i].title);
            strcpy(temp_movie_titles[movie_added], movies[i].title);
            temp_movie_indices[movie_added] = i;
            movie_added++;
        }
    }
    
    // Sort movies by similarity score (bubble sort - simple algorithm for beginner)
    for (i = 0; i < movie_added - 1; i++) {
        for (j = 0; j < movie_added - i - 1; j++) {
            if (similarity_scores[j] < similarity_scores[j + 1]) {
                // Swap scores
                int temp_score = similarity_scores[j];
                similarity_scores[j] = similarity_scores[j + 1];
                similarity_scores[j + 1] = temp_score;
                
                // Swap movie titles
                char temp_title[MOVIE_TITLE_LENGTH];
                strcpy(temp_title, temp_movie_titles[j]);
                strcpy(temp_movie_titles[j], temp_movie_titles[j + 1]);
                strcpy(temp_movie_titles[j + 1], temp_title);
                
                // Swap indices
                int temp_idx = temp_movie_indices[j];
                temp_movie_indices[j] = temp_movie_indices[j + 1];
                temp_movie_indices[j + 1] = temp_idx;
            }
        }
    }
    
    // Display top 4 recommendations
    printf("Top 4 movies similar to '%s':\n", movie_title);
    printf("----------------------------------------\n");
    
    int recommendations_shown = 0;
    for (i = 0; i < movie_added && recommendations_shown < 4; i++) {
        if (similarity_scores[i] > 0) {
            printf("%d. %s\n", recommendations_shown + 1, temp_movie_titles[i]);
            printf("   Genre: %s | Director: %s | Year: %d\n", 
                   movies[temp_movie_indices[i]].genre, 
                   movies[temp_movie_indices[i]].director,
                   movies[temp_movie_indices[i]].year);
            printf("\n");
            recommendations_shown++;
        }
    }
    
    if (recommendations_shown == 0) {
        printf("No similar movies found in our database.\n");
    }
    
    // Add the searched movie to user's history
    add_movie_to_history(user_name, movie_title);
}

// Function to display user's movie history
void display_user_history(char* user_name) {
    int user_index = find_user(user_name);
    
    if (user_index != -1) {
        printf("\n%s's movie history:\n", user_name);
        printf("------------------------\n");
        
        if (users[user_index].movie_count == 0) {
            printf("No movies in history yet.\n");
        } else {
            int i;
            for (i = 0; i < users[user_index].movie_count; i++) {
                printf("%d. %s\n", i + 1, users[user_index].watched_movies[i]);
            }
        }
        printf("\n");
    }
}

// Function to clear the screen
void clear_screen() {
    system("cls");
}