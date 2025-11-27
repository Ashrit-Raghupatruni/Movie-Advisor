# Movie Advisor - Frontend Guide

## Overview
This is a modern web-based frontend for the Movie Recommendation System. The frontend provides a beautiful, user-friendly interface to interact with the C backend.

## Files Structure

- `index.html` - Main HTML structure
- `style.css` - Modern styling and responsive design
- `app.js` - Frontend JavaScript logic
- `server.c` - HTTP server wrapper to connect frontend to C backend

## Features

1. **Modern UI Design**
   - Beautiful gradient backgrounds
   - Responsive design for all devices
   - Smooth animations and transitions
   - Dark theme with modern color scheme

2. **User Authentication**
   - Simple login with username
   - Automatic user registration
   - User history tracking

3. **Movie Search**
   - Real-time autocomplete suggestions
   - Case-insensitive search
   - Movie recommendations based on similarity

4. **Recommendations**
   - Top 4 similar movies displayed
   - Shows genre, director, and year
   - Beautiful card-based layout

5. **History Management**
   - View all watched movies
   - Automatic history saving
   - Persistent storage

## How to Run

### Option 1: Using the HTTP Server (Recommended)

1. **Compile the server:**
   ```bash
   gcc server.c -o server.exe -lws2_32
   ```

2. **Run the server:**
   ```bash
   server.exe
   ```

3. **Open in browser:**
   - Navigate to `http://localhost:8080/index.html`
   - Or simply open `index.html` in your browser (will work with local storage fallback)

### Option 2: Standalone (No Server)

1. **Simply open `index.html` in your browser**
   - The frontend will work with local storage
   - All functionality will be available
   - No backend connection required

## API Endpoints (when using server)

- `GET /api/movies` - Get all movies
- `POST /api/login` - Login/Register user
- `POST /api/recommend` - Get movie recommendations
- `POST /api/history` - Add movie to history

## Browser Compatibility

- Chrome (recommended)
- Firefox
- Edge
- Safari

## Notes

- The frontend works standalone using localStorage if the server is not running
- The server must be running on port 8080 for API integration
- All user data is saved both locally (browser) and on the server (if connected)

## Troubleshooting

1. **Server won't start:**
   - Make sure port 8080 is not in use
   - Check Windows Firewall settings
   - Run as administrator if needed

2. **Frontend not connecting:**
   - Check if server is running
   - Verify `apiBaseUrl` in `app.js` matches your server
   - Check browser console for errors

3. **CORS errors:**
   - The server includes CORS headers
   - Make sure you're accessing via `http://localhost:8080`


