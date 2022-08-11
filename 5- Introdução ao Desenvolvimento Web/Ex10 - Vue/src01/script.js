const app = Vue.createApp({
  data() {
    return {
      inputMovie: '',
      allMovies: [
        'Mulher Maravilha',
        'Brainiac',
        'Aquaman',
        'Raverna',
        'Batman',
        'Superman',
        'Mulher Gavião',
        'Flash',
        'Lanterna Verde',
        'Shazam',
      ],
      filteredMovies: [
        'Mulher Maravilha',
        'Brainiac',
        'Aquaman',
        'Raverna',
        'Batman',
        'Superman',
        'Mulher Gavião',
        'Flash',
        'Lanterna Verde',
        'Shazam',
      ],
    };
  },
  methods: {
    filterMovies() {
      this.filteredMovies = this.allMovies.filter((movie) => {
        return (
          movie.toUpperCase().indexOf(this.inputMovie.toUpperCase()) !== -1
        );
      });
    },
  },
});

app.mount('#app');
