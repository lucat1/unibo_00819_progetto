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

int Interactable::health_effect(int currentHealth, int maxHealth) {
  if (maxHealth <= 0)
    throw std::invalid_argument("Maximum health must be positive.");
  if (currentHealth < 0 || currentHealth > maxHealth)
    throw std::invalid_argument("Current health out of range.");
  const int res{unchecked_health_effect(currentHealth, maxHealth)};
  if (res < 0 || res > maxHealth)
    throw std::invalid_argument("New health is invalid.");
  return res;
}

int Interactable::mana_effect(int currentMana, int max_mana) {
  if (max_mana <= 0)
    throw std::invalid_argument("Maximum mana must be positive.");
  if (currentMana < 0 || currentMana > max_mana)
    throw std::invalid_argument("Current mana out of range.");
  const int res{unchecked_mana_effect(currentMana, max_mana)};
  if (res < 0 || res > max_mana)
    throw std::invalid_argument("New mana is invalid.");
  return res;
}

int Interactable::score_effect(int currentScore) {
  if (currentScore < 0)
    throw std::invalid_argument("Current score cannot be negative.");
  const int res{unchecked_score_effect(currentScore)};
  if (res < 0)
    throw std::invalid_argument("New score is invalid.");
  return res;
}

int Interactable::unchecked_health_effect(int currentHealth, int) {
  return currentHealth;
}

int Interactable::unchecked_mana_effect(int currentMana, int) {
  return currentMana;
}

int Interactable::unchecked_score_effect(int currentScore) {
  return currentScore;
}
