const app = Vue.createApp({
  data() {
    return {
      firstName: '',
      lastName: '',
      birthDay: '',
      email: '',
      password: '',
      sign: 'Signo',
      errors: [],
    };
  },
  methods: {
    validateInputs() {
      this.errors = [];
      // First Name Validation:
      if (this.firstName.length === 0)
        this.errors.push('O primeiro nome é obrigatório!');
      // Birthday Validation:
      if (this.birthDay.length === 0)
        this.errors.push('A data de nascimento é obrigatória!');
      else if (!/^(\d{1,2})\/(\d{1,2})\/(\d{4})$/.test(this.birthDay))
        this.errors.push('A data de nascimento est incorreta!');
      // Email validation:
      if (this.email !== '' && !/\S+@\S+\.\S+/.test(this.email))
        this.errors.push('O email está incorreto!');
      // Sign Validation:
      if (this.sign === 'Signo') this.errors.push('O signo é obrigatório!');
    },
  },
});

app.mount('#app');
