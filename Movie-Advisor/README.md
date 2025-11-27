# 🎬 Movie Advisor - Movie Recommendation System

A full-stack movie recommendation system with a C backend and modern web frontend. Get personalized movie recommendations based on genre, director, and release year.

![Movie Advisor](https://img.shields.io/badge/Movie-Advisor-blue) ![C](https://img.shields.io/badge/Language-C-orange) ![JavaScript](https://img.shields.io/badge/Frontend-JavaScript-yellow) ![License](https://img.shields.io/badge/License-MIT-green)

## 📋 Table of Contents

- [Features](#features)
- [Screenshots](#screenshots)
- [Project Structure](#project-structure)
- [Installation](#installation)
- [Usage](#usage)
- [Architecture](#architecture)
- [API Endpoints](#api-endpoints)
- [Technologies Used](#technologies-used)
- [Contributing](#contributing)
- [License](#license)

## ✨ Features

### Backend (C)
- ✅ Console-based interface
- ✅ User authentication and registration
- ✅ Movie search functionality
- ✅ Similarity-based recommendation algorithm
- ✅ User history tracking
- ✅ Data persistence in file system

### Frontend (Web)
- ✅ Modern, responsive UI design
- ✅ Beautiful gradient backgrounds and animations
- ✅ Real-time movie search with autocomplete
- ✅ Top 4 movie recommendations display
- ✅ User history management
- ✅ Works standalone or with server
- ✅ LocalStorage fallback support

## 🏗️ Project Structure

```
Movie-Advisor/
│
├── movie_recommendation_system.c  # Main C backend
├── server.c                        # HTTP server wrapper
├── index.html                      # Frontend HTML
├── style.css                       # Frontend styling
├── app.js                          # Frontend JavaScript
├── run_server.bat                  # Server startup script
├── README.md                       # This file
└── README_FRONTEND.md              # Frontend documentation
```

## 🚀 Installation

### Prerequisites

- **Windows OS** (uses Windows-specific functions)
- **GCC Compiler** (MinGW or similar)
- **Modern Web Browser** (Chrome, Firefox, Edge, Safari)

### Setup

1. **Clone the repository**
   ```bash
   git clone https://github.com/yourusername/Movie-Advisor.git
   cd Movie-Advisor
   ```

2. **Compile the backend (optional - for console version)**
   ```bash
   gcc -o movie_recommendation_system.exe movie_recommendation_system.c
   ```

3. **Compile the server (for web frontend)**
   ```bash
   gcc server.c -o server.exe -lws2_32
   ```
   
   Or use the provided batch file:
   ```bash
   run_server.bat
   ```

## 💻 Usage

### Option 1: Console Application

1. Run the compiled executable:
   ```bash
   movie_recommendation_system.exe
   ```

2. Enter your name to login
3. Use number keys to navigate:
   - `1` - Search for a movie and get recommendations
   - `2` - View your movie history
   - `ESC` - Exit

### Option 2: Web Application (Recommended)

#### With Server (Full Integration)

1. **Start the server:**
   ```bash
   server.exe
   ```
   Or double-click `run_server.bat`

2. **Open your browser:**
   ```
   http://localhost:8080
   ```

3. **Features:**
   - Enter your name to login/register
   - Search for movies with autocomplete
   - View personalized recommendations
   - Check your movie history

#### Standalone (No Server)

1. Simply open `index.html` in your browser
2. All features work with localStorage
3. No backend connection required

## 🏛️ Architecture

### Backend Algorithm

The recommendation system uses a similarity scoring algorithm:

- **Genre Match**: 50 points (same genre)
- **Director Match**: 30 points (same director)
- **Year Proximity**: Up to 20 points (closer years = more points)
  - Within 5 years: 20 - (year_diff × 2) points

Movies are sorted by similarity score and top 4 are recommended.

### Data Storage

- **User Data**: Stored in `database/user_X.txt` files
- **Movie Database**: Hardcoded in the program (25 movies across 5 genres)
- **Frontend**: Uses localStorage for offline functionality

## 🔌 API Endpoints

When using the server, the following endpoints are available:

| Method | Endpoint | Description |
|--------|----------|-------------|
| `GET` | `/api/movies` | Get all movies in database |
| `POST` | `/api/login` | Login/Register user |
| `POST` | `/api/recommend` | Get movie recommendations |
| `POST` | `/api/history` | Add movie to user history |

### Example API Usage

```javascript
// Get all movies
fetch('http://localhost:8080/api/movies')
  .then(res => res.json())
  .then(data => console.log(data));

// Get recommendations
fetch('http://localhost:8080/api/recommend', {
  method: 'POST',
  headers: { 'Content-Type': 'application/json' },
  body: JSON.stringify({ user: 'John', movie: 'The Dark Knight' })
})
  .then(res => res.json())
  .then(data => console.log(data));
```

## 🛠️ Technologies Used

### Backend
- **C Programming Language**
- **WinSock2** (for HTTP server)
- **File I/O** (for data persistence)

### Frontend
- **HTML5**
- **CSS3** (with modern features)
- **Vanilla JavaScript** (ES6+)
- **LocalStorage API**

## 📝 Movie Database

The system includes 25 movies across 5 genres:

- **Action**: The Dark Knight, Avengers: Endgame, Mad Max: Fury Road, etc.
- **Comedy**: The Grand Budapest Hotel, Superbad, Anchorman, etc.
- **Drama**: The Shawshank Redemption, Forrest Gump, The Godfather, etc.
- **Sci-Fi**: Interstellar, Blade Runner 2049, The Matrix, etc.
- **Horror**: Get Out, Hereditary, The Babadook, etc.

## 🤝 Contributing

Contributions are welcome! Please feel free to submit a Pull Request.

1. Fork the repository
2. Create your feature branch (`git checkout -b feature/AmazingFeature`)
3. Commit your changes (`git commit -m 'Add some AmazingFeature'`)
4. Push to the branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request

## 📄 License

This project is licensed under the MIT License - see the LICENSE file for details.

## 👤 Author

**Your Name**
- GitHub: [@yourusername](https://github.com/yourusername)

## 🙏 Acknowledgments

- Movie data curated from popular films
- UI design inspired by modern web applications
- Built as a learning project for C and web development

---

⭐ If you like this project, please give it a star!
