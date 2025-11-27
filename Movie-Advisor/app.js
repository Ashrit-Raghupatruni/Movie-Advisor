// Movie Advisor Frontend Application
class MovieAdvisor {
    constructor() {
        this.currentUser = null;
        this.movies = [];
        this.apiBaseUrl = 'http://localhost:8080';
        this.init();
    }

    init() {
        this.setupEventListeners();
        this.loadMovies();
    }

    setupEventListeners() {
        // Login
        document.getElementById('loginBtn').addEventListener('click', () => this.handleLogin());
        document.getElementById('userNameInput').addEventListener('keypress', (e) => {
            if (e.key === 'Enter') this.handleLogin();
        });

        // Logout
        document.getElementById('logoutBtn').addEventListener('click', () => this.handleLogout());

        // Tabs
        document.querySelectorAll('.tab-btn').forEach(btn => {
            btn.addEventListener('click', (e) => {
                const tab = e.target.dataset.tab;
                this.switchTab(tab);
            });
        });

        // Search
        document.getElementById('searchBtn').addEventListener('click', () => this.handleSearch());
        document.getElementById('movieSearchInput').addEventListener('keypress', (e) => {
            if (e.key === 'Enter') this.handleSearch();
        });

        // Autocomplete
        const searchInput = document.getElementById('movieSearchInput');
        searchInput.addEventListener('input', (e) => this.handleAutocomplete(e.target.value));
        searchInput.addEventListener('blur', () => {
            // Delay hiding suggestions to allow click events
            setTimeout(() => {
                document.getElementById('suggestions').classList.add('hidden');
            }, 200);
        });
    }

    async loadMovies() {
        try {
            const response = await fetch(`${this.apiBaseUrl}/api/movies`);
            if (response.ok) {
                this.movies = await response.json();
            } else {
                // Fallback: Use hardcoded movies if API fails
                this.loadDefaultMovies();
            }
        } catch (error) {
            console.error('Failed to load movies from API, using defaults:', error);
            this.loadDefaultMovies();
        }
    }

    loadDefaultMovies() {
        // Default movies matching the C backend
        this.movies = [
            { title: "The Dark Knight", genre: "Action", director: "Christopher Nolan", year: 2008 },
            { title: "Avengers: Endgame", genre: "Action", director: "Russo Brothers", year: 2019 },
            { title: "Mad Max: Fury Road", genre: "Action", director: "George Miller", year: 2015 },
            { title: "John Wick", genre: "Action", director: "Chad Stahelski", year: 2014 },
            { title: "Die Hard", genre: "Action", director: "John McTiernan", year: 1988 },
            { title: "The Grand Budapest Hotel", genre: "Comedy", director: "Wes Anderson", year: 2014 },
            { title: "Superbad", genre: "Comedy", director: "Greg Mottola", year: 2007 },
            { title: "Anchorman: The Legend of Ron Burgundy", genre: "Comedy", director: "Adam McKay", year: 2004 },
            { title: "Bridesmaids", genre: "Comedy", director: "Paul Feig", year: 2011 },
            { title: "Groundhog Day", genre: "Comedy", director: "Harold Ramis", year: 1993 },
            { title: "The Shawshank Redemption", genre: "Drama", director: "Frank Darabont", year: 1994 },
            { title: "Forrest Gump", genre: "Drama", director: "Robert Zemeckis", year: 1994 },
            { title: "The Godfather", genre: "Drama", director: "Francis Ford Coppola", year: 1972 },
            { title: "Pulp Fiction", genre: "Drama", director: "Quentin Tarantino", year: 1994 },
            { title: "Fight Club", genre: "Drama", director: "David Fincher", year: 1999 },
            { title: "Interstellar", genre: "Sci-Fi", director: "Christopher Nolan", year: 2014 },
            { title: "Blade Runner 2049", genre: "Sci-Fi", director: "Denis Villeneuve", year: 2017 },
            { title: "The Matrix", genre: "Sci-Fi", director: "Wachowski Sisters", year: 1999 },
            { title: "Arrival", genre: "Sci-Fi", director: "Denis Villeneuve", year: 2016 },
            { title: "Ex Machina", genre: "Sci-Fi", director: "Alex Garland", year: 2014 },
            { title: "Get Out", genre: "Horror", director: "Jordan Peele", year: 2017 },
            { title: "Hereditary", genre: "Horror", director: "Ari Aster", year: 2018 },
            { title: "The Babadook", genre: "Horror", director: "Jennifer Kent", year: 2014 },
            { title: "A Quiet Place", genre: "Horror", director: "John Krasinski", year: 2018 },
            { title: "The Conjuring", genre: "Horror", director: "James Wan", year: 2013 }
        ];
    }

    async handleLogin() {
        const userName = document.getElementById('userNameInput').value.trim();
        if (!userName) {
            this.showError('Please enter your name');
            return;
        }

        this.showLoading();
        try {
            // Try to login via API
            const response = await fetch(`${this.apiBaseUrl}/api/login`, {
                method: 'POST',
                headers: { 'Content-Type': 'application/json' },
                body: JSON.stringify({ name: userName })
            });

            if (response.ok) {
                const data = await response.json();
                this.currentUser = { name: userName, history: data.history || [] };
            } else {
                // Fallback: Create user locally
                this.currentUser = { name: userName, history: this.getUserHistory(userName) || [] };
            }
        } catch (error) {
            // Fallback: Create user locally
            this.currentUser = { name: userName, history: this.getUserHistory(userName) || [] };
        }

        this.hideLoading();
        this.showApp();
    }

    handleLogout() {
        this.currentUser = null;
        document.getElementById('userNameInput').value = '';
        this.showLogin();
    }

    showLogin() {
        document.getElementById('loginSection').classList.remove('hidden');
        document.getElementById('appSection').classList.add('hidden');
    }

    showApp() {
        document.getElementById('loginSection').classList.add('hidden');
        document.getElementById('appSection').classList.remove('hidden');
        document.getElementById('userNameDisplay').textContent = this.currentUser.name;
        this.loadUserHistory();
    }

    switchTab(tabName) {
        // Update tab buttons
        document.querySelectorAll('.tab-btn').forEach(btn => {
            btn.classList.remove('active');
            if (btn.dataset.tab === tabName) {
                btn.classList.add('active');
            }
        });

        // Update tab content
        document.querySelectorAll('.tab-content').forEach(content => {
            content.classList.remove('active');
        });

        if (tabName === 'search') {
            document.getElementById('searchTab').classList.add('active');
        } else if (tabName === 'history') {
            document.getElementById('historyTab').classList.add('active');
            this.loadUserHistory();
        }
    }

    handleAutocomplete(query) {
        const suggestionsDiv = document.getElementById('suggestions');
        if (!query || query.length < 2) {
            suggestionsDiv.classList.add('hidden');
            return;
        }

        const queryLower = query.toLowerCase();
        const matches = this.movies.filter(movie => 
            movie.title.toLowerCase().includes(queryLower)
        ).slice(0, 5);

        if (matches.length === 0) {
            suggestionsDiv.classList.add('hidden');
            return;
        }

        suggestionsDiv.innerHTML = matches.map(movie => 
            `<div class="suggestion-item" data-title="${movie.title}">${movie.title}</div>`
        ).join('');

        suggestionsDiv.classList.remove('hidden');

        // Add click handlers
        suggestionsDiv.querySelectorAll('.suggestion-item').forEach(item => {
            item.addEventListener('click', () => {
                document.getElementById('movieSearchInput').value = item.dataset.title;
                suggestionsDiv.classList.add('hidden');
                this.handleSearch();
            });
        });
    }

    async handleSearch() {
        const movieTitle = document.getElementById('movieSearchInput').value.trim();
        if (!movieTitle) {
            this.showError('Please enter a movie title');
            return;
        }

        const movie = this.findMovie(movieTitle);
        if (!movie) {
            this.showError(`Sorry, we don't have information about '${movieTitle}' in our database.`);
            return;
        }

        this.showLoading();
        
        try {
            // Try to get recommendations from API
            const response = await fetch(`${this.apiBaseUrl}/api/recommend`, {
                method: 'POST',
                headers: { 'Content-Type': 'application/json' },
                body: JSON.stringify({ 
                    user: this.currentUser.name, 
                    movie: movieTitle 
                })
            });

            let recommendations = [];
            if (response.ok) {
                const data = await response.json();
                recommendations = data.recommendations || [];
            } else {
                // Fallback: Calculate recommendations locally
                recommendations = this.getRecommendations(movieTitle);
            }

            // Add movie to history
            this.addMovieToHistory(movieTitle);

            this.displayRecommendations(movieTitle, recommendations);
        } catch (error) {
            // Fallback: Calculate recommendations locally
            const recommendations = this.getRecommendations(movieTitle);
            this.addMovieToHistory(movieTitle);
            this.displayRecommendations(movieTitle, recommendations);
        }

        this.hideLoading();
    }

    findMovie(title) {
        return this.movies.find(movie => 
            movie.title.toLowerCase() === title.toLowerCase()
        );
    }

    getRecommendations(movieTitle) {
        const movie = this.findMovie(movieTitle);
        if (!movie) return [];

        const recommendations = this.movies
            .filter(m => m.title.toLowerCase() !== movieTitle.toLowerCase())
            .map(m => ({
                movie: m,
                score: this.getSimilarityScore(movie, m)
            }))
            .filter(r => r.score > 0)
            .sort((a, b) => b.score - a.score)
            .slice(0, 4)
            .map(r => r.movie);

        return recommendations;
    }

    getSimilarityScore(movie1, movie2) {
        let score = 0;

        // Same genre: 50 points
        if (movie1.genre === movie2.genre) {
            score += 50;
        }

        // Same director: 30 points
        if (movie1.director === movie2.director) {
            score += 30;
        }

        // Year proximity: up to 20 points
        const yearDiff = Math.abs(movie1.year - movie2.year);
        if (yearDiff <= 5) {
            score += 20 - (yearDiff * 2);
        }

        return score;
    }

    displayRecommendations(movieTitle, recommendations) {
        const section = document.getElementById('recommendationsSection');
        const title = document.getElementById('recommendationsTitle');
        const grid = document.getElementById('recommendationsGrid');

        title.textContent = `Movies similar to "${movieTitle}"`;
        
        if (recommendations.length === 0) {
            grid.innerHTML = '<p class="empty-state">No similar movies found in our database.</p>';
        } else {
            grid.innerHTML = recommendations.map(movie => `
                <div class="movie-card">
                    <h4>${movie.title}</h4>
                    <div class="movie-info">
                        <div class="movie-info-item">
                            <strong>Genre:</strong>
                            <span>${movie.genre}</span>
                        </div>
                        <div class="movie-info-item">
                            <strong>Director:</strong>
                            <span>${movie.director}</span>
                        </div>
                        <div class="movie-info-item">
                            <strong>Year:</strong>
                            <span>${movie.year}</span>
                        </div>
                    </div>
                </div>
            `).join('');
        }

        section.classList.remove('hidden');
        this.switchTab('search');
    }

    addMovieToHistory(movieTitle) {
        if (!this.currentUser) return;

        if (!this.currentUser.history.includes(movieTitle)) {
            this.currentUser.history.push(movieTitle);
            this.saveUserHistory();
        }

        // Try to save via API
        fetch(`${this.apiBaseUrl}/api/history`, {
            method: 'POST',
            headers: { 'Content-Type': 'application/json' },
            body: JSON.stringify({
                user: this.currentUser.name,
                movie: movieTitle
            })
        }).catch(err => console.error('Failed to save history via API:', err));
    }

    loadUserHistory() {
        if (!this.currentUser) return;

        const historyList = document.getElementById('historyList');
        
        if (this.currentUser.history.length === 0) {
            historyList.innerHTML = '<p class="empty-state">No movies in your history yet. Start searching to build your collection!</p>';
        } else {
            historyList.innerHTML = this.currentUser.history.map((movie, index) => `
                <div class="history-item">
                    <span class="history-item-title">${index + 1}. ${movie}</span>
                </div>
            `).join('');
        }
    }

    getUserHistory(userName) {
        const stored = localStorage.getItem(`user_${userName}_history`);
        return stored ? JSON.parse(stored) : [];
    }

    saveUserHistory() {
        if (!this.currentUser) return;
        localStorage.setItem(`user_${this.currentUser.name}_history`, JSON.stringify(this.currentUser.history));
    }

    showLoading() {
        document.getElementById('loadingOverlay').classList.remove('hidden');
    }

    hideLoading() {
        document.getElementById('loadingOverlay').classList.add('hidden');
    }

    showError(message) {
        const errorDiv = document.getElementById('errorMessage');
        errorDiv.textContent = message;
        errorDiv.classList.remove('hidden');
        setTimeout(() => {
            errorDiv.classList.add('hidden');
        }, 3000);
    }
}

// Initialize the application when DOM is loaded
document.addEventListener('DOMContentLoaded', () => {
    new MovieAdvisor();
});


