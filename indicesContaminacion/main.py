#Creado por Elías Rodríguez A01654900
#Descarga información del índice de la calidad del aire en la cdmx de http://aire.cdmx.gob.mx/opendata/IndiceCalidadAire/ de 1992 a 2022
#21/05/2021, análisis de ciencia de datos
#Última modificación: 21/05/2021
#Versión 1.0, hecho para windows, python 3.10.7
#Bibliotecas que se importan: os, shutil, matplotlib.pyplot, pandas, numpy, requests, time
#
#
#Drive a los plots que genera este código: https://drive.google.com/drive/folders/1-96dhepWAAXpGgkRiubPlglZyNqTTZyX?usp=share_link
#Porque puede tardar un poco
#
#
#
#Instrucciones de uso:
#Ejecutar con: python main.exe
#Se crearan archivos y carpetas, por lo que se recomienda usar una carpeta nueva


import os
import shutil
import matplotlib.pyplot as plt
import pandas as pd
import numpy as np
import requests
from time import sleep


intervalo=10000

#función de descarga de archivos
def pull():
    delay=0.1
    inicio="http://aire.cdmx.gob.mx/opendata/IndiceCalidadAire/"
    año=1992
    terminacion=".csv"
    url= inicio + "indice_" + str(año) + terminacion

    while año < 2023:
        print(f"Descargando... {url}")
        try:
            response = requests.get(url)
        except:
            print("Error al descargar el archivo")
            break
        else:
            try:
                os.mkdir("./archivos")
            except:
                pass
            finally:
                with open(f"./archivos/indice_{año}{terminacion}", "wb") as file:
                    file.write(response.content)
                    año += 1
                    url= inicio + "indice_" + str(año) + terminacion
                    sleep(delay)
    print("Descarga finalizada")


#crea un solo archivo con todos los datos
def junta_datos():
    direccion="./archivos/indice_"
    años=range(1992,2023)
    terminacion=".csv"
    lista_df=[]
    #quita los metadatos de los archivos
    for año in años:
        lista_df.append(pd.read_csv(direccion + str(año) + terminacion, skiprows=8, encoding="latin-1", on_bad_lines="skip"))
    #concatena los archivos
    df=pd.concat(lista_df)
    #guarda el archivo
    df.to_csv("./indice_completo.csv", index=False)



def creaArchivos():
    #Crea un archivo txt que checa si ./archivos existe
    #Si no existe, lo crea
    #tiempo, lugar, contaminantes. 
    try:        
        if os.path.isfile("./indice_completo.csv"):
            return
        os.mkdir("./archivos")
        #checa si existe el archivo indice_comleto.csv
        #si existe, no hace nada, regresa
    except:
        pass
    else:
        pull()
        junta_datos()
        print("Proceso finalizado")
        print("El archivo se encuentra en ./archivos/indice_completo.csv")
        print("Limpiando...")
        #elimina la carpeta y los archivos dentro, windows
        shutil.rmtree("./archivos")
    



def main():
    global intervalo
    creaArchivos()
    df=pd.read_csv("indice_completo.csv")
    #drop last 17 columns
    df=df.iloc[:,:-17]
    print(df.head())
    print(df.tail())
    print(df.describe())
    fechaHora=df.iloc[:,0:2]
    df=df.iloc[:,2:]

    #loop through all the columns and fill interpolate NA values

    #antes del suavizado, como va 


    printGraph(df, fechaHora, "Sin suavizado")


    print("Interploando...")
    for column in df.columns:
        df[column]=df[column].interpolate()
    df=df.dropna()
    df.head()
    df.tail()
    df.describe()

    #numpy convolve

    print("Preparando intervalo fijo...")
    for column in df.columns:
        #fix TypeError: can't multiply sequence by non-int of type 'float'
        df[column]=df[column].astype(float)
        df[column]=np.convolve(df[column], np.ones(intervalo), mode="same")/intervalo

    printGraph(df, fechaHora, f"Suavizado cada {intervalo} de datos")
    #use a gaussian kernel to smooth the data
    df3=df.copy()
    print("Preparando kernel gaussiano...")
    for column in df3.columns:
        df3[column]=df3[column].rolling(intervalo, win_type="gaussian").mean(std=5)
    printGraph(df3, fechaHora, f"Kernel Gaussiano")

    print("Preparando kernel triangular...")
    #Kernel triangular 
    df4=df.copy()
    for column in df4.columns:
        df4[column]=df4[column].rolling(intervalo, win_type="triang").mean()
    printGraph(df4, fechaHora, f"Kernel Triangular")

    print("Preparando histograma...")
    #finalmente, el histograma de todas las columnas del df original
    df.hist(figsize=(20,20))
    plt.savefig("./plots/histograma.png")
    plt.show()
    plt.close()




def printGraph(df, fechaHora, title):
    global intervalo
    #print 7 columns at a time in one plot, all columns, use fechaHora for x axis
    each=5
    os.makedirs("./plots", exist_ok=True)
    for i in range(0, len(df.columns), each):
        df.iloc[:,i:i+each].plot()
        plt.xticks(np.arange(0, len(df), intervalo), fechaHora.iloc[0:len(df):intervalo,0], rotation=90)
        plt.title(title)
        plt.savefig(f"./plots/{title}_{i/each}.png")
        plt.show()
        plt.close()


if __name__ == "__main__":
    main()
