#Simulacion de Monte Carlo y plot de Armenteros
#El plot de Armenteros es una tecnica de seleccion de eventos comunmente usado en estudios de fisica de iones pesados
#El proposito es poder lograr distinguir entre los kaones_0 y los lamda's_0

#Se importan las librerias mas importantes

import numpy as np
import pandas as pd
import math
import matplotlib.pyplot as plt
from matplotlib import cm as CM
from matplotlib import mlab as ML
import seaborn as sns

#Numero de eventos a simular
nEvent = 10000

#Masas de las particulas involucradas en MeV

mkaon = 497.671
mpion = 139.56
mlambda = 1115.63
mproton = 938.272

#Creacion de array para las variables finales a graficar
names = ['alpha','p1T']

data = pd.DataFrame(np.zeros((1000, 2)),columns=names)

data.index+=1

#print data.head()

for event in range(1,nEvent+1):
  randomNumber  = np.random.rand()
  
  if randomNumber < 0.5:            # Se simula el 50% decayendo un kaon_0 a dos piones de signo opuesto
    m = mkaon
    m_1 = mpion
    m_2 = mpion
  elif 0.5 < randomNumber < 0.75:   # Se simula el 25% decayendo un lambda_0 un proton y pion negativo
    m = mlambda
    m_1 = mproton
    m_2 = mpion
  else:                             # Se simula el 25% decayendo un lambda_0 a pion negativo y proton
    m = mlambda                     
    m_1 = mpion
    m_2 = mproton

    
#Se emplea una distribucion gaussiana para la energia de la particula M que va a decaer
  E =  np.random.normal(2*m, 0.02*m, 1)

  p = np.sqrt(E**2-m**2)               #Determinamos el momento lineal

#Se definen estas variables para aplicar transformaciones de Lorentz en el sistema S' y el sistema de laboratorio S
  gamma = E/m
  gammaBeta = p/m

#Se encuentran las energias de los productos de decaimiento en el sistema S'
  E_1_prima = (m**2+m_1**2-m_2**2)/(2*m) 
  E_2_prima = (m**2-m_1**2+m_2**2)/(2*m)

#Asi como la magnitud de sus momentos:
  p_1_prima = np.sqrt(E_1_prima**2-m_1**2)
  p_2_prima = np.sqrt(E_2_prima**2-m_2**2)

#Aplicando la condicion de isotropia en los productos de decaimiento para los angulos
  phi_1_prima =  np.random.uniform(0, 2*np.pi)
  theta_1_prima = math.acos(np.random.uniform(0, 2)-1)

#Se obtienen las componentes de momento lineal para la primera particula de decaimiento m_1
  p_1x_prima= p_1_prima*math.sin(theta_1_prima)*math.cos(phi_1_prima)
  p_1y_prima= p_1_prima*math.sin(theta_1_prima)*math.sin(phi_1_prima)
  p_1z_prima= p_1_prima*math.cos(theta_1_prima)

#De la misma forma para la segunda particula de decaimiento m_2 por conservacion de momento
  p_2x_prima = -p_1x_prima
  p_2y_prima = -p_1y_prima
  p_2z_prima = -p_1z_prima

#Ahora volvemos al sistema S de laboratorio aplicando transformaciones de Lorentz para encontrar las energias y los momentos de los productos de decaimiento

  E_1 = gamma*E_1_prima +gammaBeta*p_1x_prima
  p_1x = gamma*p_1x_prima + gammaBeta*E_1_prima
  p_1y = p_1y_prima
  p_1z = p_1z_prima
  
  E_2 = gamma*E_2_prima +gammaBeta*p_2x_prima
  p_2x = gamma*p_2x_prima + gammaBeta*E_2_prima
  p_2y = p_2y_prima
  p_2z = p_2z_prima

#Se determina los angulos de los productos de decaimiento en el sistema S
  theta_1 = math.atan((np.sqrt(p_1x**2 + p_1y**2))/p_1z)
  theta_2 = math.atan((np.sqrt(p_2x**2 + p_2y**2))/p_2z)

#Asi mismo se establecen las condiciones para cada uno de los angulos en los respectivos cuadrantes:
  if p_1z<0:
    theta_1 = math.atan((np.sqrt(p_1x**2 + p_1y**2))/p_1z)+np.pi
  if p_2z<0: 
    theta_2 = math.atan((np.sqrt(p_2x**2 + p_2y**2))/p_2z)+np.pi
  if p_1x>0 and p_1y>0:
    phi_1 = math.atan(p_1y/p_1x)
  elif p_1x<0 and p_1y<0:
    phi_1 = math.atan(p_1y/p_1x)+np.pi
  elif p_1x<0 and p_1y>0:
    phi_1 = math.atan(p_1y/p_1x)+np.pi
  else:
    phi_1 = math.atan(p_1y/p_1x)+2*np.pi
  if p_2x>0 and p_2y>0:
    phi_2 = math.atan(p_2y/p_2x)
  elif p_2x<0 and p_2y<0:
    phi_2 = math.atan(p_2y/p_2x)+np.pi
  elif p_2x<0 and p_2y>0:
    phi_2 = math.atan(p_2y/p_2x)+np.pi
  else:
    phi_2 = math.atan(p_2y/p_2x)+2*np.pi

#Debido a la resolucion del detector se introduce un smearing a cada una de las variables que se van a inplementar
  E_1_obs = np.random.normal(E_1, abs(0.001*E_1), 1)
  E_2_obs = np.random.normal(E_2, abs(0.001*E_2), 1)

  theta_1_obs = np.random.normal(theta_1, abs(0.001*theta_1), 1)
  theta_2_obs = np.random.normal(theta_2, abs(0.001*theta_2), 1)

  phi_1_obs = np.random.normal(phi_1, abs(0.001*phi_1), 1)
  phi_2_obs = np.random.normal(phi_2, abs(0.001*phi_2), 1)

#Se encuentran las magnitudes de los momentos observados
  p_1_obs=np.sqrt((E_1_obs)**2-(m_1)**2)
  p_2_obs=np.sqrt((E_2_obs)**2-(m_2)**2)

#Luego para cada una de las componenentes de momento:
  p_1x_obs = p_1_obs*math.sin(theta_1_obs)*math.cos(phi_1_obs)
  p_1y_obs = p_1_obs*math.sin(theta_1_obs)*math.sin(phi_1_obs)
  p_1z_obs = p_1_obs*math.cos(theta_1_obs)

  p_2x_obs = p_2_obs*math.sin(theta_2_obs)*math.cos(phi_2_obs)
  p_2y_obs = p_2_obs*math.sin(theta_2_obs)*math.sin(phi_2_obs)
  p_2z_obs = p_2_obs*math.cos(theta_2_obs)

#Expresando el momentum en terminos de las componentes longitudinales y transversales
  p_1_L = p_1x_obs
  p_2_L = p_2x_obs
  p_1_T = np.sqrt(p_1y_obs**2+p_1z_obs**2)
  p_2_T = np.sqrt(p_2y_obs**2+p_2z_obs**2)

#Expresando alpha como (en terminos de los momento longitudinales):
  alpha = (p_1_L-p_2_L)/(p_1_L+p_2_L)
  
  data.loc[event,'alpha'] = alpha
  data.loc[event,'p1T'] = p_1_T
    
# Generando el plot final de Armenteros donde se representa el momento transverso de los productos de decaimiento cargados como funcion del momento longitudinal asimetrico (alpha)
x = np.random.randn(8873)
y = np.random.randn(8873)
ax = sns.jointplot(x=data['alpha'].values, y=data['p1T'].values, kind='hex',size=10,cmap=CM.jet,color='b',gridsize=70)
plt.ylabel('p1T(MeV/c)', fontsize=14)
plt.xlabel('Alpha', fontsize=14)
plt.show()
ax.savefig('p1T vs Alpha.pdf')

#Se obtiene el plot donde puede observar finalmente el decaimiento del kaon_0 y los lambda's_0 en base al analisis de las propiedades cinematicas de sus productos de decaimiento

