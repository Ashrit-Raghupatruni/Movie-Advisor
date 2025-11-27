#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>
#include <windows.h>
#include <ctype.h>

#pragma comment(lib, "ws2_32.lib")

// Include the backend functions (we'll link them)
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

// Function declarations from backend
int string_compare_ignore_case(char* str1, char* str2);
void load_default_movies();
void load_user_data();
void save_user_data(int user_index);
int find_user(char* name);
int register_user(char* name);
int find_movie(char* title);
void add_movie_to_history(char* user_name, char* movie_title);
int get_similarity_score(char* movie1, char* movie2);
void get_recommendations_json(char* user_name, char* movie_title, char* output, int output_size);

#define PORT 8080
#define BUFFER_SIZE 8192

// Function to compare two strings ignoring case
int string_compare_ignore_case(char* str1, char* str2) {
    int i = 0;
    while (str1[i] && str2[i]) {
        if (tolower(str1[i]) != tolower(str2[i])) {
            return 0;
        }
        i++;
    }
    if (str1[i] == '\0' && str2[i] == '\0') {
        return 1;
    }
    return 0;
}

// Function to load default movies (simplified version)
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
    
    // Create database directory if it doesn't exist
    CreateDirectory("database", NULL);
    
    for (i = 0; i < MAX_USERS; i++) {
        sprintf(filename, "database\\user_%d.txt", i);
        file = fopen(filename, "r");
        if (file != NULL) {
            if (fscanf(file, "%s\n", users[user_count].name) == 1) {
                fscanf(file, "%d\n", &users[user_count].movie_count);
                
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
    
    CreateDirectory("database", NULL);
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
    return -1;
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
    int movie1_idx = find_movie(movie1);
    int movie2_idx = find_movie(movie2);
    
    if (movie1_idx == -1 || movie2_idx == -1) {
        return 0;
    }
    
    int score = 0;
    
    if (strcmp(movies[movie1_idx].genre, movies[movie2_idx].genre) == 0) {
        score += 50;
    }
    
    if (strcmp(movies[movie1_idx].director, movies[movie2_idx].director) == 0) {
        score += 30;
    }
    
    int year_diff = abs(movies[movie1_idx].year - movies[movie2_idx].year);
    if (year_diff <= 5) {
        score += 20 - (year_diff * 2);
    }
    
    return score;
}

// Function to get recommendations as JSON
void get_recommendations_json(char* user_name, char* movie_title, char* output, int output_size) {
    int i, j;
    int similarity_scores[MAX_MOVIES];
    int temp_movie_indices[MAX_MOVIES];
    char temp_movie_titles[MAX_MOVIES][MOVIE_TITLE_LENGTH];
    int movie_added = 0;
    
    // Calculate similarity scores
    for (i = 0; i < movie_count; i++) {
        if (string_compare_ignore_case(movies[i].title, movie_title) == 0) {
            similarity_scores[movie_added] = get_similarity_score(movie_title, movies[i].title);
            strcpy(temp_movie_titles[movie_added], movies[i].title);
            temp_movie_indices[movie_added] = i;
            movie_added++;
        }
    }
    
    // Sort by similarity score (bubble sort)
    for (i = 0; i < movie_added - 1; i++) {
        for (j = 0; j < movie_added - i - 1; j++) {
            if (similarity_scores[j] < similarity_scores[j + 1]) {
                int temp_score = similarity_scores[j];
                similarity_scores[j] = similarity_scores[j + 1];
                similarity_scores[j + 1] = temp_score;
                
                char temp_title[MOVIE_TITLE_LENGTH];
                strcpy(temp_title, temp_movie_titles[j]);
                strcpy(temp_movie_titles[j], temp_movie_titles[j + 1]);
                strcpy(temp_movie_titles[j + 1], temp_title);
                
                int temp_idx = temp_movie_indices[j];
                temp_movie_indices[j] = temp_movie_indices[j + 1];
                temp_movie_indices[j + 1] = temp_idx;
            }
        }
    }
    
    // Build JSON response
    strcpy(output, "{\"recommendations\":[");
    int recommendations_shown = 0;
    for (i = 0; i < movie_added && recommendations_shown < 4; i++) {
        if (similarity_scores[i] > 0) {
            if (recommendations_shown > 0) {
                strcat(output, ",");
            }
            
            char movie_json[500];
            sprintf(movie_json, "{\"title\":\"%s\",\"genre\":\"%s\",\"director\":\"%s\",\"year\":%d}",
                    movies[temp_movie_indices[i]].title,
                    movies[temp_movie_indices[i]].genre,
                    movies[temp_movie_indices[i]].director,
                    movies[temp_movie_indices[i]].year);
            strcat(output, movie_json);
            recommendations_shown++;
        }
    }
    strcat(output, "]}");
}

// Function to extract JSON value
void extract_json_value(char* json, char* key, char* value, int value_size) {
    char search_key[100];
    sprintf(search_key, "\"%s\":\"", key);
    char* start = strstr(json, search_key);
    if (start) {
        start += strlen(search_key);
        char* end = strchr(start, '"');
        if (end) {
            int len = end - start;
            if (len < value_size) {
                strncpy(value, start, len);
                value[len] = '\0';
            }
        }
    }
}

// Function to send HTTP response
void send_response(SOCKET client_socket, int status_code, char* content_type, char* body) {
    char response[BUFFER_SIZE];
    sprintf(response, "HTTP/1.1 %d OK\r\n"
                     "Content-Type: %s\r\n"
                     "Access-Control-Allow-Origin: *\r\n"
                     "Access-Control-Allow-Methods: GET, POST, OPTIONS\r\n"
                     "Access-Control-Allow-Headers: Content-Type\r\n"
                     "Content-Length: %d\r\n"
                     "\r\n%s",
            status_code, content_type, (int)strlen(body), body);
    send(client_socket, response, strlen(response), 0);
}

// Function to read file content
int read_file_content(char* filename, char* buffer, int buffer_size) {
    FILE* file = fopen(filename, "rb");
    if (!file) return 0;
    
    int bytes_read = fread(buffer, 1, buffer_size - 1, file);
    buffer[bytes_read] = '\0';
    fclose(file);
    return bytes_read;
}

// Function to get content type from filename
char* get_content_type(char* filename) {
    if (strstr(filename, ".html")) return "text/html";
    if (strstr(filename, ".css")) return "text/css";
    if (strstr(filename, ".js")) return "application/javascript";
    if (strstr(filename, ".json")) return "application/json";
    return "text/plain";
}

// Function to handle API requests
void handle_request(SOCKET client_socket, char* request) {
    char method[10], path[256];
    sscanf(request, "%s %s", method, path);
    
    // Handle CORS preflight
    if (strstr(request, "OPTIONS")) {
        send_response(client_socket, 200, "application/json", "");
        return;
    }
    
    // Serve static files
    if (strcmp(method, "GET") == 0) {
        char filepath[300];
        if (strcmp(path, "/") == 0 || strcmp(path, "/index.html") == 0) {
            strcpy(filepath, "index.html");
        } else if (strstr(path, ".html") || strstr(path, ".css") || strstr(path, ".js")) {
            // Remove leading slash
            strcpy(filepath, path + 1);
        } else {
            strcpy(filepath, "");
        }
        
        if (strlen(filepath) > 0) {
            char file_content[50000];
            int bytes_read = read_file_content(filepath, file_content, sizeof(file_content));
            if (bytes_read > 0) {
                char* content_type = get_content_type(filepath);
                send_response(client_socket, 200, content_type, file_content);
                return;
            }
        }
    }
    
    // GET /api/movies
    if (strcmp(method, "GET") == 0 && strcmp(path, "/api/movies") == 0) {
        char json[10000] = "{\"movies\":[";
        int i;
        for (i = 0; i < movie_count; i++) {
            if (i > 0) strcat(json, ",");
            char movie_json[200];
            sprintf(movie_json, "{\"title\":\"%s\",\"genre\":\"%s\",\"director\":\"%s\",\"year\":%d}",
                    movies[i].title, movies[i].genre, movies[i].director, movies[i].year);
            strcat(json, movie_json);
        }
        strcat(json, "]}");
        send_response(client_socket, 200, "application/json", json);
        return;
    }
    
    // POST /api/login
    if (strcmp(method, "POST") == 0 && strcmp(path, "/api/login") == 0) {
        char* body_start = strstr(request, "\r\n\r\n");
        if (body_start) {
            body_start += 4;
            char name[NAME_LENGTH];
            extract_json_value(body_start, "name", name, sizeof(name));
            
            int user_index = find_user(name);
            if (user_index == -1) {
                user_index = register_user(name);
            }
            
            char json[5000] = "{\"history\":[";
            int i;
            for (i = 0; i < users[user_index].movie_count; i++) {
                if (i > 0) strcat(json, ",");
                char movie_str[150];
                sprintf(movie_str, "\"%s\"", users[user_index].watched_movies[i]);
                strcat(json, movie_str);
            }
            strcat(json, "]}");
            send_response(client_socket, 200, "application/json", json);
            return;
        }
    }
    
    // POST /api/recommend
    if (strcmp(method, "POST") == 0 && strcmp(path, "/api/recommend") == 0) {
        char* body_start = strstr(request, "\r\n\r\n");
        if (body_start) {
            body_start += 4;
            char user[NAME_LENGTH], movie[MOVIE_TITLE_LENGTH];
            extract_json_value(body_start, "user", user, sizeof(user));
            extract_json_value(body_start, "movie", movie, sizeof(movie));
            
            if (find_movie(movie) != -1) {
                add_movie_to_history(user, movie);
                char recommendations[5000];
                get_recommendations_json(user, movie, recommendations, sizeof(recommendations));
                send_response(client_socket, 200, "application/json", recommendations);
                return;
            }
        }
    }
    
    // POST /api/history
    if (strcmp(method, "POST") == 0 && strcmp(path, "/api/history") == 0) {
        char* body_start = strstr(request, "\r\n\r\n");
        if (body_start) {
            body_start += 4;
            char user[NAME_LENGTH], movie[MOVIE_TITLE_LENGTH];
            extract_json_value(body_start, "user", user, sizeof(user));
            extract_json_value(body_start, "movie", movie, sizeof(movie));
            
            add_movie_to_history(user, movie);
            send_response(client_socket, 200, "application/json", "{\"status\":\"ok\"}");
            return;
        }
    }
    
    // Default response
    send_response(client_socket, 404, "text/plain", "Not Found");
}

int main() {
    WSADATA wsa;
    SOCKET server_socket, client_socket;
    struct sockaddr_in server, client;
    int client_len = sizeof(client);
    char buffer[BUFFER_SIZE];
    
    printf("=== Movie Advisor HTTP Server ===\n");
    printf("Initializing...\n");
    
    // Initialize Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        printf("Failed. Error Code: %d\n", WSAGetLastError());
        return 1;
    }
    
    // Load data
    load_default_movies();
    load_user_data();
    printf("Loaded %d movies and %d users\n", movie_count, user_count);
    
    // Create socket
    if ((server_socket = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
        printf("Could not create socket: %d\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }
    
    // Prepare sockaddr_in structure
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(PORT);
    
    // Bind
    if (bind(server_socket, (struct sockaddr*)&server, sizeof(server)) == SOCKET_ERROR) {
        printf("Bind failed with error code: %d\n", WSAGetLastError());
        closesocket(server_socket);
        WSACleanup();
        return 1;
    }
    
    // Listen
    listen(server_socket, 3);
    printf("Server listening on port %d\n", PORT);
    printf("Open http://localhost:%d/index.html in your browser\n", PORT);
    
    // Accept incoming connections
    while (1) {
        client_socket = accept(server_socket, (struct sockaddr*)&client, &client_len);
        if (client_socket == INVALID_SOCKET) {
            printf("Accept failed with error code: %d\n", WSAGetLastError());
            continue;
        }
        
        // Receive request
        int recv_size = recv(client_socket, buffer, BUFFER_SIZE - 1, 0);
        if (recv_size > 0) {
            buffer[recv_size] = '\0';
            handle_request(client_socket, buffer);
        }
        
        closesocket(client_socket);
    }
    
    closesocket(server_socket);
    WSACleanup();
    return 0;
}

