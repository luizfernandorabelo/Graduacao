'use strict';

class Client {
  constructor(name, address) {
    this.name = name;
    this.address = address;
  }
}

class BankAccount {
  #balance;
  #interest;

  constructor(client, balance, interest) {
    this.client = client;
    this.#balance = balance;
    this.#interest = interest;
  }

  getBalance() {
    return this.#balance;
  }

  getInterest() {
    return this.#interest;
  }

  setInterest(interest) {
    this.#interest = interest;
  }

  withdraw(amount) {
    this.#balance -= amount;
  }

  deposit(amount) {
    this.#balance += amount;
  }

  applyInterest() {
    this.#balance *= 1 + this.#interest;
  }
}

let bankAccount = null;

document.querySelector('#create-account-btn').addEventListener('click', () => {
  if (bankAccount !== null) {
    alert('Conta já criada!');
    return;
  }

  let name = prompt('Digite seu nome');
  let address = prompt('Digite seu endereço');
  let interest = 0.1,
    initialBalance = 0;
  if (
    confirm(
      'Pressione OK para personalizar o saldo inicial e os juros ' +
        'ou CANCELAR para carregar os valores padrão (saldo = 0 e juros = 10%)'
    )
  ) {
    initialBalance = parseFloat(prompt('Digite o saldo inicial'));
    interest = parseFloat(prompt('Digite a taxa de juros (de 0 a 100)')) / 100;
  }
  bankAccount = new BankAccount(
    new Client(name, address),
    initialBalance,
    interest
  );
});

document.querySelector('#deposit-money-btn').addEventListener('click', () => {
  if (bankAccount == null) {
    alert('Você precisa criar uma conta para depositar dinheiro!');
    return;
  }

  let amount = parseFloat(prompt('Digite a quantidade a ser depositada'));

  if (amount < 0) {
    alert('Quantidade inválida!');
    return;
  }

  bankAccount.deposit(amount);

  alert('Dinheiro depositado com sucesso!');
  alert('Seu novo saldo é de R$ ' + bankAccount.getBalance());
});

document
  .querySelector('#deposit-interest-earnings-btn')
  .addEventListener('click', () => {
    if (bankAccount == null) {
      alert('Você precisa criar uma conta para aplicar juros!');
      return;
    }

    bankAccount.applyInterest();

    alert('Juros aplicados com sucesso!');
    alert('Seu novo saldo é de R$ ' + bankAccount.getBalance());
  });

document.querySelector('#withdraw-money-btn').addEventListener('click', () => {
  if (bankAccount == null) {
    alert('Você precisa criar uma conta para sacar dinheiro!');
    return;
  }

  let amount = parseFloat(prompt('Digite a quantidade a ser sacada'));

  if (amount < 0) {
    alert('Quantidade inválida!');
    return;
  }

  if (amount > bankAccount.getBalance()) {
    alert('Seu saldo não é suficiente!');
    return;
  }

  bankAccount.withdraw(amount);

  alert('Dinheiro sacado com sucesso!');
  alert('Seu novo saldo é de R$ ' + bankAccount.getBalance());
});

document.querySelector('#show-balance-btn').addEventListener('click', () => {
  if (bankAccount == null) {
    alert('Você precisa criar uma conta para ver seu saldo!');
    return;
  }

  alert('Seu saldo é de R$ ' + bankAccount.getBalance());
});
