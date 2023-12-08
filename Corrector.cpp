#include "stdafx.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include "corrector.h"
#define DEPURAR 05

void Diccionario(char* szNombre, char szPalabras[][TAMTOKEN], int iEstadisticas[], int& iNumElementos) {
    FILE* fpDicc;
    char linea[4000];
    char palabraDetectada[TAMTOKEN];
    int i;
    int indicePD;
    char aux;
    char guargar[TAMTOKEN];
    char szLetras[] = { 'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z','á','é','í','ó','ú' };
    iNumElementos = 0;
    if (DEPURAR == 1) {
        printf("%s", szNombre);
    }
    fopen_s(&fpDicc, szNombre, "r");
    if (fpDicc != NULL) {
        if (DEPURAR == 1) {
            printf("\nSi lo pude abrir");
        }
        indicePD = 0;
        while (!feof(fpDicc)) {
            fgets(linea, sizeof(linea), fpDicc);
            _strlwr(linea);
            if (DEPURAR == 1) {
                printf("\n%s\n", linea);
            }
            for (i = 0; i < strlen(linea); i++) {
                if (linea[i] == ' ' || linea[i] == '.') {
                    iEstadisticas[iNumElementos] = 1;
                    for (int i = 0; i < iNumElementos; i++) {
                        if (strcmp(szPalabras[i], palabraDetectada) == 0) {
                            iEstadisticas[i]++;
                            indicePD = 0;
                        }
                    }
                    palabraDetectada[indicePD] = '\0';
                    if (palabraDetectada[0] != '\0' && palabraDetectada[0] != '\n' && palabraDetectada[0] != '\t') {
                        strcpy_s(szPalabras[iNumElementos], TAMTOKEN, palabraDetectada);
                        if (DEPURAR == 1) {
                            printf("\np: %s", palabraDetectada);
                        }
                        indicePD = 0;
                        iNumElementos++;
                    }
                }
                else {
                    if (linea[i] != '(' && linea[i] != ')' && linea[i] != ':' && linea[i] != '´' && linea[i] != '#' && linea[i] != ',' && linea[i] != '\n' && linea[i] != ' ' && linea[i] != '\0') {
                        palabraDetectada[indicePD] = (linea[i]);
                        indicePD++;
                    }
                }
            }
            if (DEPURAR == 1) {
                printf("\nNumPalabras: %i\n", iNumElementos);
            }
            if (DEPURAR == 1) {
                int j = 0;
                for (i = 0; i < iNumElementos; i++) {
                    printf("prueba: %s \n", szPalabras[j]);
                    j++;
                }
            }
        }
        fclose(fpDicc);
    }
    else {
        if (DEPURAR == 1) {
            printf("\nNo lo pude abrir");
        }
    }
    for (int j = 0; j < iNumElementos - 1; j++) {
        for (i = j + 1; i < iNumElementos; i++) {
            if (strcmp(szPalabras[j], szPalabras[i]) > 0) {
                strcpy_s(guargar, szPalabras[j]);
                strcpy_s(szPalabras[j], szPalabras[i]);
                strcpy_s(szPalabras[i], guargar);
                aux = iEstadisticas[j];
                iEstadisticas[j] = iEstadisticas[i];
                iEstadisticas[i] = aux;
            }
        }
    }
}

void ClonaPalabras(char* szPalabraLeida, char szPalabrasSugeridas[][TAMTOKEN], int& iNumSugeridas) {
    int i, j, k;
    char aux[TAMTOKEN];
    char iNumSugeridas = 0;
    char szLetras[] = { 'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z','á','é','í','ó','ú' };
    strcpy_s(aux, szPalabraLeida);
    if (DEPURAR == 1) {
        printf("palabra leida: %s", aux);
    }
    for (i = 0; i < strlen(szPalabraLeida); i++) {
        for (j = 0; j < strlen(szLetras); j++) {
            aux[i] = szLetras[j];
            strcpy_s(szPalabrasSugeridas[iNumSugeridas++], aux);
        }
        aux[i] = szPalabraLeida[i];
    }
    for (k = 1; k < strlen(szPalabraLeida) + 1; k++) {
        aux[k] = szPalabraLeida[k - 1];
    }
    aux[k] = '\0';
    for (int i = 0; i < strlen(szPalabraLeida) + 1; i++) {
        for (int j = 0; j < strlen(szLetras); j++) {
            aux[i] = szLetras[j];
            strcpy_s(szPalabrasSugeridas[iNumSugeridas++], aux);
        }
        aux[i] = szPalabraLeida[i];
    }
    k = 0;
    for (i = 0; i < strlen(szPalabraLeida) && strlen(szPalabraLeida) != 1; i++) {
        for (j = 0; j < strlen(szPalabraLeida); j++) {
            if (j != i)
                aux[k++] = szPalabraLeida[j];
        }
        aux[k] = '\0';
        strcpy_s(szPalabrasSugeridas[iNumSugeridas++], aux);
        strcpy_s(aux, szPalabraLeida);
        k = 0;
    }
    for (i = 0; i < strlen(szPalabraLeida) - 1; i++) {
        aux[i] = szPalabraLeida[i + 1];
        aux[i + 1] = szPalabraLeida[i];
        strcpy_s(szPalabrasSugeridas[iNumSugeridas++], aux);
        strcpy_s(aux, szPalabraLeida);
    }
    strcpy_s(szPalabrasSugeridas[iNumSugeridas++], szPalabraLeida);
    for (j = 0; j < iNumSugeridas - 1; j++) {
        for (i = j + 1; i < iNumSugeridas; i++) {
            if (strcmp(szPalabrasSugeridas[j], szPalabrasSugeridas[i]) > 0) {
                strcpy_s(aux, szPalabrasSugeridas[j]);
                strcpy_s(szPalabrasSugeridas[j], szPalabrasSugeridas[i]);
                strcpy_s(szPalabrasSugeridas[i], aux);
            }
        }
    }
}

void ListaCandidatas(char szPalabrasSugeridas[][TAMTOKEN], int iNumSugeridas, char szPalabras[][TAMTOKEN], int iEstadisticas[], int iNumElementos, char szListaFinal[][TAMTOKEN], int iPeso[], int& iNumLista) {
    int iAux;
    char szAux[TAMTOKEN];
    iNumLista = 0;
    int i, j, k;
    for (i = 0; i < iNumSugeridas; i++) {
        for (j = 0; j < iNumElementos; j++) {
            if (strcmp(szPalabrasSugeridas[i], szPalabras[j]) == 0) {
                bool bandera = false;
                for (k = 0; k < iNumLista && !bandera; k++)
                    if (strcmp(szListaFinal[k], szPalabras[j]) == 0)
                        bandera = true;
                if (bandera) continue;
                strcpy_s(szListaFinal[iNumLista], szPalabrasSugeridas[i]);
                iPeso[iNumLista++] = iEstadisticas[j];
            }
        }
    }
    for (i = 0; i < iNumLista; i++) {
        for (j = 0; j < iNumLista - 1; j++) {
            if (iPeso[j] < iPeso[j + 1]) {
                strcpy_s(szAux, szListaFinal[j + 1]);
                iAux = iPeso[j + 1];
                strcpy_s(szListaFinal[j + 1], szListaFinal[j]);
                iPeso[j + 1] = iPeso[j];
                strcpy_s(szListaFinal[j], szAux);
                iPeso[j] = iAux;
            }
        }
    }
}