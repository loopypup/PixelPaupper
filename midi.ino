#include "midi.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

const unsigned short midiSizes[] = {168, 159, 150, 141, 133, 126, 119, 112, 106, 100, 94, 89, 84, 79, 75, 70, 66, 63, 59, 56, 53, 50, 47, 44, 42, 39, 37, 35, 33, 31, 29, 28, 26, 25, 23, 22, 21, 1};
const byte midi48[168] = {127, 131, 136, 141, 145, 150, 155, 159, 164, 168, 173, 177, 182, 186, 190, 194, 198, 202, 206, 209, 213, 216, 220, 223, 226, 229, 231, 234, 236, 239, 241, 243, 245, 246, 248, 249, 250, 251, 252, 253, 253, 253, 254, 253, 253, 253, 252, 251, 250, 249, 248, 246, 245, 243, 241, 239, 236, 234, 231, 229, 226, 223, 220, 216, 213, 209, 206, 202, 198, 194, 190, 186, 182, 177, 173, 168, 164, 159, 155, 150, 145, 141, 136, 131, 127, 122, 117, 112, 108, 103, 98, 94, 89, 85, 80, 76, 71, 67, 63, 59, 55, 51, 47, 44, 40, 37, 33, 30, 27, 24, 22, 19, 17, 14, 12, 10, 8, 7, 5, 4, 3, 2, 1, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 4, 5, 7, 8, 10, 12, 14, 17, 19, 22, 24, 27, 30, 33, 37, 40, 44, 47, 51, 55, 59, 63, 67, 71, 76, 80, 85, 89, 94, 98, 103, 108, 112, 117, 122, }; 
const byte midi49[159] = {127, 132, 137, 142, 146, 151, 156, 161, 166, 171, 175, 180, 184, 189, 193, 197, 202, 206, 209, 213, 217, 220, 224, 227, 230, 233, 235, 238, 240, 242, 244, 246, 248, 249, 250, 251, 252, 253, 253, 253, 253, 253, 253, 252, 252, 251, 250, 248, 247, 245, 243, 241, 239, 236, 234, 231, 228, 225, 222, 218, 215, 211, 207, 204, 200, 195, 191, 187, 182, 178, 173, 168, 164, 159, 154, 149, 144, 139, 134, 129, 124, 119, 114, 109, 104, 99, 94, 89, 85, 80, 75, 71, 66, 62, 58, 53, 49, 46, 42, 38, 35, 31, 28, 25, 22, 19, 17, 14, 12, 10, 8, 6, 5, 3, 2, 1, 1, 0, 0, 0, 0, 0, 0, 1, 2, 3, 4, 5, 7, 9, 11, 13, 15, 18, 20, 23, 26, 29, 33, 36, 40, 44, 47, 51, 56, 60, 64, 69, 73, 78, 82, 87, 92, 97, 102, 107, 111, 116, 121, }; 
const byte midi50[150] = {127, 132, 137, 142, 148, 153, 158, 163, 168, 173, 178, 183, 188, 192, 197, 201, 205, 209, 213, 217, 221, 224, 228, 231, 234, 236, 239, 241, 244, 246, 247, 249, 250, 251, 252, 253, 253, 253, 253, 253, 253, 252, 251, 250, 249, 247, 246, 244, 241, 239, 236, 234, 231, 228, 224, 221, 217, 213, 209, 205, 201, 197, 192, 188, 183, 178, 173, 168, 163, 158, 153, 148, 142, 137, 132, 127, 121, 116, 111, 105, 100, 95, 90, 85, 80, 75, 70, 65, 61, 56, 52, 48, 44, 40, 36, 32, 29, 25, 22, 19, 17, 14, 12, 9, 7, 6, 4, 3, 2, 1, 0, 0, 0, 0, 0, 0, 1, 2, 3, 4, 6, 7, 9, 12, 14, 17, 19, 22, 25, 29, 32, 36, 40, 44, 48, 52, 56, 61, 65, 70, 75, 80, 85, 90, 95, 100, 105, 111, 116, 121, }; 
const byte midi51[141] = {127, 132, 138, 143, 149, 155, 160, 165, 171, 176, 181, 186, 191, 196, 201, 205, 210, 214, 218, 222, 225, 229, 232, 235, 238, 240, 243, 245, 247, 249, 250, 251, 252, 253, 253, 253, 253, 253, 253, 252, 251, 249, 248, 246, 244, 242, 239, 236, 234, 230, 227, 223, 220, 216, 212, 207, 203, 198, 194, 189, 184, 179, 173, 168, 163, 157, 152, 146, 141, 135, 129, 124, 118, 112, 107, 101, 96, 90, 85, 80, 74, 69, 64, 59, 55, 50, 46, 41, 37, 33, 30, 26, 23, 19, 17, 14, 11, 9, 7, 5, 4, 2, 1, 0, 0, 0, 0, 0, 0, 1, 2, 3, 4, 6, 8, 10, 13, 15, 18, 21, 24, 28, 31, 35, 39, 43, 48, 52, 57, 62, 67, 72, 77, 82, 88, 93, 98, 104, 110, 115, 121, }; 
const byte midi52[133] = {127, 132, 138, 144, 150, 156, 162, 168, 173, 179, 184, 190, 195, 200, 205, 209, 214, 218, 222, 226, 229, 233, 236, 239, 242, 244, 246, 248, 250, 251, 252, 253, 253, 253, 253, 253, 252, 252, 250, 249, 247, 245, 243, 240, 237, 234, 231, 228, 224, 220, 216, 211, 207, 202, 197, 192, 187, 182, 176, 171, 165, 159, 153, 147, 141, 135, 129, 124, 118, 112, 106, 100, 94, 88, 82, 77, 71, 66, 61, 56, 51, 46, 42, 37, 33, 29, 25, 22, 19, 16, 13, 10, 8, 6, 4, 3, 1, 1, 0, 0, 0, 0, 0, 1, 2, 3, 5, 7, 9, 11, 14, 17, 20, 24, 27, 31, 35, 39, 44, 48, 53, 58, 63, 69, 74, 80, 85, 91, 97, 103, 109, 115, 121, }; 
const byte midi53[126] = {127, 133, 139, 145, 152, 158, 164, 170, 176, 182, 187, 193, 198, 203, 208, 213, 217, 222, 226, 230, 233, 236, 240, 242, 245, 247, 249, 250, 252, 253, 253, 253, 253, 253, 253, 252, 250, 249, 247, 245, 242, 240, 236, 233, 230, 226, 222, 217, 213, 208, 203, 198, 193, 187, 182, 176, 170, 164, 158, 152, 145, 139, 133, 127, 120, 114, 108, 101, 95, 89, 83, 77, 71, 66, 60, 55, 50, 45, 40, 36, 31, 27, 23, 20, 17, 13, 11, 8, 6, 4, 3, 1, 0, 0, 0, 0, 0, 0, 1, 3, 4, 6, 8, 11, 13, 17, 20, 23, 27, 31, 36, 40, 45, 50, 55, 60, 66, 71, 77, 83, 89, 95, 101, 108, 114, 120, }; 
const byte midi54[119] = {127, 133, 140, 147, 153, 160, 166, 172, 179, 185, 190, 196, 202, 207, 212, 217, 221, 226, 230, 234, 237, 240, 243, 246, 248, 250, 251, 252, 253, 253, 253, 253, 253, 252, 250, 249, 247, 244, 242, 239, 235, 232, 228, 224, 219, 215, 210, 204, 199, 193, 188, 182, 175, 169, 163, 156, 150, 143, 137, 130, 123, 116, 110, 103, 97, 90, 84, 78, 71, 65, 60, 54, 49, 43, 38, 34, 29, 25, 21, 18, 14, 11, 9, 6, 4, 3, 1, 0, 0, 0, 0, 0, 1, 2, 3, 5, 7, 10, 13, 16, 19, 23, 27, 32, 36, 41, 46, 51, 57, 63, 68, 74, 81, 87, 93, 100, 106, 113, 120, }; 
const byte midi55[112] = {127, 134, 141, 148, 155, 162, 168, 175, 182, 188, 194, 200, 206, 211, 216, 221, 226, 230, 234, 238, 241, 244, 246, 249, 250, 252, 253, 253, 254, 253, 253, 252, 250, 249, 246, 244, 241, 238, 234, 230, 226, 221, 216, 211, 206, 200, 194, 188, 182, 175, 168, 162, 155, 148, 141, 134, 127, 119, 112, 105, 98, 91, 85, 78, 71, 65, 59, 53, 47, 42, 37, 32, 27, 23, 19, 15, 12, 9, 7, 4, 3, 1, 0, 0, 0, 0, 0, 1, 3, 4, 7, 9, 12, 15, 19, 23, 27, 32, 37, 42, 47, 53, 59, 65, 71, 78, 85, 91, 98, 105, 112, 119, }; 
const byte midi56[106] = {127, 134, 142, 149, 156, 164, 171, 178, 184, 191, 197, 204, 209, 215, 220, 225, 230, 234, 238, 241, 244, 247, 249, 251, 252, 253, 253, 253, 253, 252, 251, 249, 247, 244, 241, 238, 234, 230, 225, 220, 215, 209, 204, 197, 191, 184, 178, 171, 164, 156, 149, 142, 134, 127, 119, 111, 104, 97, 89, 82, 75, 69, 62, 56, 49, 44, 38, 33, 28, 23, 19, 15, 12, 9, 6, 4, 2, 1, 0, 0, 0, 0, 1, 2, 4, 6, 9, 12, 15, 19, 23, 28, 33, 38, 44, 49, 56, 62, 69, 75, 82, 89, 97, 104, 111, 119, }; 
const byte midi57[100] = {127, 134, 142, 150, 158, 166, 173, 181, 188, 195, 201, 207, 213, 219, 224, 229, 234, 238, 241, 245, 247, 250, 251, 252, 253, 254, 253, 252, 251, 250, 247, 245, 241, 238, 234, 229, 224, 219, 213, 207, 201, 195, 188, 181, 173, 166, 158, 150, 142, 134, 127, 119, 111, 103, 95, 87, 80, 72, 65, 58, 52, 46, 40, 34, 29, 24, 19, 15, 12, 8, 6, 3, 2, 1, 0, 0, 0, 1, 2, 3, 6, 8, 12, 15, 19, 24, 29, 34, 40, 46, 52, 58, 65, 72, 80, 87, 95, 103, 111, 119, }; 
const byte midi58[94] = {127, 135, 143, 152, 160, 168, 176, 184, 191, 198, 205, 212, 218, 223, 229, 234, 238, 242, 245, 248, 250, 252, 253, 253, 253, 253, 252, 250, 248, 245, 242, 238, 234, 229, 223, 218, 212, 205, 198, 191, 184, 176, 168, 160, 152, 143, 135, 127, 118, 110, 101, 93, 85, 77, 69, 62, 55, 48, 41, 35, 30, 24, 19, 15, 11, 8, 5, 3, 1, 0, 0, 0, 0, 1, 3, 5, 8, 11, 15, 19, 24, 30, 35, 41, 48, 55, 62, 69, 77, 85, 93, 101, 110, 118, }; 
const byte midi59[89] = {127, 135, 144, 153, 162, 170, 179, 187, 194, 202, 209, 216, 222, 227, 233, 237, 241, 245, 248, 250, 252, 253, 253, 253, 253, 251, 249, 246, 243, 239, 235, 230, 225, 219, 212, 205, 198, 191, 183, 175, 166, 158, 149, 140, 131, 122, 113, 104, 95, 87, 78, 70, 62, 55, 48, 41, 34, 28, 23, 18, 14, 10, 7, 4, 2, 0, 0, 0, 0, 1, 3, 5, 8, 12, 16, 20, 26, 31, 37, 44, 51, 59, 66, 74, 83, 91, 100, 109, 118, }; 
const byte midi60[84] = {127, 136, 145, 155, 164, 173, 182, 190, 198, 206, 213, 220, 226, 231, 236, 241, 245, 248, 250, 252, 253, 254, 253, 252, 250, 248, 245, 241, 236, 231, 226, 220, 213, 206, 198, 190, 182, 173, 164, 155, 145, 136, 127, 117, 108, 98, 89, 80, 71, 63, 55, 47, 40, 33, 27, 22, 17, 12, 8, 5, 3, 1, 0, 0, 0, 1, 3, 5, 8, 12, 17, 22, 27, 33, 40, 47, 55, 63, 71, 80, 89, 98, 108, 117, }; 
const byte midi61[79] = {127, 137, 147, 157, 166, 176, 185, 194, 202, 210, 217, 224, 230, 236, 240, 245, 248, 250, 252, 253, 253, 253, 251, 249, 246, 243, 238, 233, 227, 221, 214, 206, 198, 189, 180, 171, 161, 152, 142, 132, 121, 111, 101, 92, 82, 73, 64, 55, 47, 39, 32, 26, 20, 15, 10, 7, 4, 2, 0, 0, 0, 1, 3, 5, 8, 13, 17, 23, 29, 36, 43, 51, 59, 68, 77, 87, 96, 106, 116, }; 
const byte midi62[75] = {127, 137, 148, 158, 168, 178, 188, 197, 205, 213, 221, 228, 234, 239, 244, 247, 250, 252, 253, 253, 253, 251, 249, 246, 241, 236, 231, 224, 217, 209, 201, 192, 183, 173, 163, 153, 142, 132, 121, 111, 100, 90, 80, 70, 61, 52, 44, 36, 29, 22, 17, 12, 7, 4, 2, 0, 0, 0, 1, 3, 6, 9, 14, 19, 25, 32, 40, 48, 56, 65, 75, 85, 95, 105, 116, }; 
const byte midi63[70] = {127, 138, 149, 160, 171, 182, 192, 201, 210, 218, 226, 232, 238, 243, 247, 250, 252, 253, 253, 252, 250, 247, 243, 238, 232, 226, 218, 210, 201, 192, 182, 171, 160, 149, 138, 127, 115, 104, 93, 82, 71, 61, 52, 43, 35, 27, 21, 15, 10, 6, 3, 1, 0, 0, 1, 3, 6, 10, 15, 21, 27, 35, 43, 52, 61, 71, 82, 93, 104, 115, }; 
const byte midi64[66] = {127, 139, 151, 162, 174, 185, 195, 205, 214, 222, 230, 236, 242, 247, 250, 252, 253, 253, 252, 250, 247, 242, 236, 230, 222, 214, 205, 195, 185, 174, 162, 151, 139, 127, 114, 102, 91, 79, 68, 58, 48, 39, 31, 23, 17, 11, 6, 3, 1, 0, 0, 1, 3, 6, 11, 17, 23, 31, 39, 48, 58, 68, 79, 91, 102, 114, }; 
const byte midi65[63] = {127, 139, 152, 164, 176, 187, 198, 208, 217, 226, 233, 240, 245, 249, 252, 253, 253, 253, 250, 247, 242, 236, 230, 222, 213, 203, 193, 182, 170, 158, 145, 133, 120, 108, 95, 83, 71, 60, 50, 40, 31, 23, 17, 11, 6, 3, 0, 0, 0, 1, 4, 8, 13, 20, 27, 36, 45, 55, 66, 77, 89, 101, 114, }; 
const byte midi66[59] = {127, 140, 153, 166, 179, 191, 202, 213, 222, 230, 238, 244, 248, 251, 253, 253, 252, 250, 246, 241, 234, 226, 217, 208, 197, 185, 173, 160, 147, 133, 120, 106, 93, 80, 68, 56, 45, 36, 27, 19, 12, 7, 3, 1, 0, 0, 2, 5, 9, 15, 23, 31, 40, 51, 62, 74, 87, 100, 113, }; 
const byte midi67[56] = {127, 141, 155, 168, 182, 194, 206, 216, 226, 234, 241, 246, 250, 253, 254, 253, 250, 246, 241, 234, 226, 216, 206, 194, 182, 168, 155, 141, 127, 112, 98, 85, 71, 59, 47, 37, 27, 19, 12, 7, 3, 0, 0, 0, 3, 7, 12, 19, 27, 37, 47, 59, 71, 85, 98, 112, }; 
const byte midi68[53] = {127, 142, 156, 171, 184, 197, 209, 220, 230, 238, 244, 249, 252, 253, 253, 251, 247, 241, 234, 225, 215, 204, 191, 178, 164, 149, 134, 119, 104, 89, 75, 62, 49, 38, 28, 19, 12, 6, 2, 0, 0, 1, 4, 9, 15, 23, 33, 44, 56, 69, 82, 97, 111, }; 
const byte midi69[50] = {127, 142, 158, 173, 188, 201, 213, 224, 234, 241, 247, 251, 253, 253, 251, 247, 241, 234, 224, 213, 201, 188, 173, 158, 142, 127, 111, 95, 80, 65, 52, 40, 29, 19, 12, 6, 2, 0, 0, 2, 6, 12, 19, 29, 40, 52, 65, 80, 95, 111, }; 
const byte midi70[47] = {127, 143, 160, 176, 191, 205, 218, 229, 238, 245, 250, 253, 253, 252, 248, 242, 234, 223, 212, 198, 184, 168, 152, 135, 118, 101, 85, 69, 55, 41, 30, 19, 11, 5, 1, 0, 0, 3, 8, 15, 24, 35, 48, 62, 77, 93, 110, }; 
const byte midi71[44] = {127, 145, 162, 179, 195, 210, 222, 233, 242, 248, 252, 254, 252, 248, 242, 233, 222, 210, 195, 179, 162, 145, 127, 108, 91, 74, 58, 43, 31, 20, 11, 5, 1, 0, 1, 5, 11, 20, 31, 43, 58, 74, 91, 108, }; 
const byte midi72[42] = {127, 145, 164, 182, 198, 213, 226, 236, 245, 250, 253, 253, 250, 245, 236, 226, 213, 198, 182, 164, 145, 127, 108, 89, 71, 55, 40, 27, 17, 8, 3, 0, 0, 3, 8, 17, 27, 40, 55, 71, 89, 108, }; 
const byte midi73[39] = {127, 147, 167, 186, 203, 218, 231, 241, 248, 253, 253, 251, 245, 236, 225, 211, 194, 176, 157, 137, 116, 96, 77, 59, 42, 28, 17, 8, 2, 0, 0, 5, 12, 22, 35, 50, 67, 86, 106, }; 
const byte midi74[37] = {127, 148, 169, 188, 206, 222, 235, 244, 251, 253, 252, 248, 240, 229, 214, 198, 179, 159, 137, 116, 94, 74, 55, 39, 24, 13, 5, 1, 0, 2, 9, 18, 31, 47, 65, 84, 105, }; 
const byte midi75[35] = {127, 149, 171, 192, 210, 226, 238, 247, 252, 253, 250, 243, 232, 218, 201, 182, 160, 138, 115, 93, 71, 52, 35, 21, 10, 3, 0, 1, 6, 15, 27, 43, 61, 82, 104, }; 
const byte midi76[33] = {127, 151, 174, 195, 214, 230, 242, 250, 253, 252, 247, 236, 222, 205, 185, 162, 139, 114, 91, 68, 48, 31, 17, 6, 1, 0, 3, 11, 23, 39, 58, 79, 102, }; 
const byte midi77[31] = {127, 152, 177, 199, 219, 234, 246, 252, 253, 249, 241, 227, 209, 188, 165, 139, 114, 88, 65, 44, 26, 12, 4, 0, 1, 7, 19, 34, 54, 76, 101, }; 
const byte midi78[29] = {127, 154, 180, 203, 223, 239, 249, 253, 252, 244, 232, 214, 192, 167, 140, 113, 86, 61, 39, 21, 9, 1, 0, 4, 14, 30, 50, 73, 99, }; 
const byte midi79[28] = {127, 155, 182, 206, 226, 241, 250, 254, 250, 241, 226, 206, 182, 155, 127, 98, 71, 47, 27, 12, 3, 0, 3, 12, 27, 47, 71, 98, }; 
const byte midi80[26] = {127, 157, 186, 211, 231, 245, 253, 253, 245, 231, 211, 186, 157, 126, 96, 67, 42, 22, 8, 0, 0, 8, 22, 42, 67, 96, }; 
const byte midi81[25] = {127, 158, 188, 213, 234, 247, 253, 251, 241, 224, 201, 173, 142, 111, 80, 52, 29, 12, 2, 0, 6, 19, 40, 65, 95, }; 
const byte midi82[23] = {127, 161, 192, 219, 239, 251, 253, 246, 230, 207, 177, 144, 109, 76, 46, 23, 7, 0, 2, 14, 34, 61, 92, }; 
const byte midi83[22] = {127, 162, 195, 222, 242, 252, 252, 242, 222, 195, 162, 127, 91, 58, 31, 11, 1, 1, 11, 31, 58, 91, }; 
const byte midi84[21] = {127, 164, 198, 226, 245, 253, 250, 236, 213, 182, 145, 108, 71, 40, 17, 3, 0, 8, 27, 55, 89, };
const byte silence[1] = {0, };
byte const * midis[MIDI_MAX - MIDI_MIN + 1 + 1];

void setupMidi()
{
  midis[0] = midi48;
  midis[1] = midi49;
  midis[2] = midi50;
  midis[3] = midi51;
  midis[4] = midi52;
  midis[5] = midi53;
  midis[6] = midi54;
  midis[7] = midi55;
  midis[8] = midi56;
  midis[9] = midi57;
  midis[10] = midi58;
  midis[11] = midi59;
  midis[12] = midi60;
  midis[13] = midi61;
  midis[14] = midi62;
  midis[15] = midi63;
  midis[16] = midi64;
  midis[17] = midi65;
  midis[18] = midi66;
  midis[19] = midi67;
  midis[20] = midi68;
  midis[21] = midi69;
  midis[22] = midi70;
  midis[23] = midi71;
  midis[24] = midi72;
  midis[25] = midi73;
  midis[26] = midi74;
  midis[27] = midi75;
  midis[28] = midi76;
  midis[29] = midi77;
  midis[30] = midi78;
  midis[31] = midi79;
  midis[32] = midi80;
  midis[33] = midi81;
  midis[34] = midi82;
  midis[35] = midi83;
  midis[36] = midi84;
  midis[37] = silence;
}

Note makeNote(float duration, byte midi)
{
  Note n;
  n.duration = duration * SAMPLE_RATE;
  n.midi = midi - MIDI_MIN;
  return n;
}

Song * makeSong(float * durations, byte * midis, uint32_t num)
{
  Note * notes = (Note *) malloc( sizeof(Note) * num );
  Song * song = (Song *) malloc(sizeof(Song));
  uint32_t i = 0;

  song->numNotes = num;
  song->curNoteTime = 0;
  song->notes = notes;
  song->flags = 0;
  song->curTime = 0;
  song->curNote = 0;
  
  for (;i < num; i++)
  {
    notes[i].duration = durations[i] * SAMPLE_RATE;
    notes[i].midi = midis[i] - MIDI_MIN;
  }

  song->curMidi = notes[0].midi;
  song->curDuration = song->notes[0].duration;
  
  return song;
}

byte updateSong(Song * song)
{ 
  static byte isNoise;
  isNoise = song->curMidi == NOISE;
  
  if ( !isNoise && ++song->curNoteTime >= midiSizes[song->curMidi])
  {
    song->curNoteTime = 0;
  }

  if (++song->curTime >= song->curDuration)
  {
    song->curTime = 0;
    song->curNoteTime = 0;
    song->curNote++;

    //Perhaps do a loop check here
    if (song->curNote == song->numNotes)
    {
      song->curNote = 0;
    }
  
    song->curMidi = song->notes[song->curNote].midi;
    song->curDuration = song->notes[song->curNote].duration;
  }

  if (isNoise)
  {
    return rand() % 127;
  }
  else
  {
    return midis[song->curMidi][song->curNoteTime];
  }
}
