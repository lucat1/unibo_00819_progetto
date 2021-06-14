/*
  University of Bologna
  First cicle degree in Computer Science
  00819 - Programmazione

  Stefano Volpe #969766
  04/28/2021

  hero.cpp: implementation of Data::Interactables::Hero and its helper entities.
*/

#include "hero.hpp"

using Data::Pawns::Hero;

const Nostd::WString &Hero::name() const noexcept { return nm; }

wchar_t Hero::sprite() const noexcept { return sprt; }
