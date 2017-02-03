/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   packet.h
 * Author: dangche1
 *
 * Created on February 2, 2017, 5:47 PM
 */

#pragma once

struct packet{
    unsigned total_frag; 
    unsigned frag_no;
    unsigned size;
    char* filename;
    char filedata[1000];
};

