/*
 * Slot class: function implementations
 * CSF Assignment 3
 * Caroline Zhao
 * czhao67@jhu.edu
 * Miranda Qing
 * mqing2@jhu.edu
 */

#include "slot.h"

Slot::Slot() {
    tag = -1;
    valid = false;
    dirty = false;
    load_ts = 0;
    access_ts = 0;
}

Slot::Slot( int t, int loadTime ) {
    tag = t;
    valid = false;
    dirty = false;
    load_ts = loadTime;
    access_ts = loadTime;
}

int Slot::getTag() {
    return tag;
}

bool Slot::getValid() {
    return valid;
}

bool Slot::getDirty() {
    return dirty;
}

int Slot::getLoadTS() {
    return load_ts;
}

int Slot::getAccessTS() {
    return access_ts;
}

void Slot::updateTag( int t ) {
    tag = t;
}

void Slot::toggleValid() {
    valid = !valid;
}	

void Slot::setDirty( bool d ) {
    dirty = d;
}

void Slot::setLoadTS( int currentSimTime ) {
    load_ts = currentSimTime;
}

void Slot::setAccessTS( int currentSimTime ) {
    access_ts = currentSimTime;
}