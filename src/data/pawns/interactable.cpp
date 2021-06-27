/*
  University of Bologna
  First cicle degree in Computer Science
  00819 - Programmazione

  Stefano Volpe #969766
  06/14/2021

  interactable.cpp: implementation of Data::Pawns::Interactable.
*/

#include "interactable.hpp"

#include <stdexcept>

using Data::Pawns::Interactable;

Interactable &Interactable::operator=(Interactable &&i) {
  Pawn::operator=(i);
  return *this;
}

int Interactable::healthEffect(int currentHealth, int maxHealth) {
  if (maxHealth <= 0)
    throw std::invalid_argument("Maximum health must be positive.");
  if (currentHealth < 0 || currentHealth > maxHealth)
    throw std::invalid_argument("Current health out of range.");
  const int res{uncheckedHealthEffect(currentHealth, maxHealth)};
  if (res < 0 || res > maxHealth)
    throw std::invalid_argument("New health is invalid.");
  return res;
}

int Interactable::manaEffect(int currentMana, int maxMana) {
  if (maxMana <= 0)
    throw std::invalid_argument("Maximum mana must be positive.");
  if (currentMana < 0 || currentMana > maxMana)
    throw std::invalid_argument("Current mana out of range.");
  const int res{uncheckedManaEffect(currentMana, maxMana)};
  if (res < 0 || res > maxMana)
    throw std::invalid_argument("New mana is invalid.");
  return res;
}

int Interactable::scoreEffect(int currentScore) {
  if (currentScore < 0)
    throw std::invalid_argument("Current score cannot be negative.");
  const int res{uncheckedScoreEffect(currentScore)};
  if (res < 0)
    throw std::invalid_argument("New score is invalid.");
  return res;
}

int Interactable::uncheckedHealthEffect(int currentHealth, int) {
  return currentHealth;
}

int Interactable::uncheckedManaEffect(int currentMana, int) {
  return currentMana;
}

int Interactable::uncheckedScoreEffect(int currentScore) {
  return currentScore;
}
