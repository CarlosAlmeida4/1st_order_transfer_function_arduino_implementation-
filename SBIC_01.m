% clc
% clear all
% close all
% 
% %%
% %SBIC_0.1
% 
% R=1.6e3;
% C=2e-6;
% Ts=0.5e-3;
% S=tf('s');
% 
% %G=1/(R*C*S+1)
% G=tf([1], [R*C 1])
% 
% figure
% step(G)
% hold on
% t=0:0.01:5;
% 
% %u=sin(1*t);
% 
% %lsim(G,u,t)
% 
% %%
% %Discretização
% 
% Gz=c2d(G,0.5e-3,'Tustin')
% 
% step(Gz)
% 
% %%
% 
% 
% RC=R*C;
% 
% RC_=5*RC
% 
% figure
% bode(G)

%%
%SBIC_0.2
% 
% 
% R=1e3;
% C=1e-6;
% Ts=0.5e-3;
% S=tf('s');
% 
% %G=1/(R*C*S+1)
% G=tf([1], [R*C 1])
% 
% figure
% step(G)
% hold on
% t=0:0.01:5;
% 
% u=sin(1*t);
% 
% %lsim(G,u,t)
% 
% %%
% %Discretização
% 
% Gz=c2d(G,0.5e-3,'Tustin');
% 
% step(Gz);
% 
% %%
% %transformada inversa
% 
% RC=R*C
% 
% RC_=5*RC
% 
% figure;
% bode(G);

% %%
% %SBIC_0.3
% 
% R=100;
% C=1e-6;
% Ts=0.1e-3;
% S=tf('s');
% 
% %G=1/(R*C*S+1)
% G=tf([1], [R*C 1])
% 
% figure
% step(G)
% hold on
% t=0:0.01:5;
% 
% u=sin(1*t);
% 
% %lsim(G,u,t)
% 
% %%
% %Discretização
% 
% Gz=c2d(G,Ts,'Tustin')
% 
% step(Gz)
% 
% %%
% %transformada inversa
% 
% RC=R*C
% 
% RC_=5*RC
% 
% 1/RC_
% figure
% bode(G)

%%
%SBIC_0.5
%Sistema1

R=1.6e3;
C=2e-6;
Ts=1e-3;
S=tf('s');

%G=1/(R*C*S+1)
G=tf([1], [R*C 1])

figure
step(G)
hold on
t=0:0.01:5;

u=sin(1*t);

%lsim(G,u,t)


%%
%Discretização

Gz1=c2d(G,Ts,'Tustin')

step(Gz1)

%%
%transformada inversa

RC=R*C

RC_=5*RC

figure
bode(G)

%%
%Sistema2


R=500;
C=10e-6;

S=tf('s');

%G=1/(R*C*S+1)
G=tf([1], [R*C 1])

figure
step(G)
hold on
t=0:0.01:5;

u=sin(1*t);

%lsim(G,u,t)

%%
%Discretização

Gz2=c2d(G,Ts,'Tustin')

step(Gz2)

%%
%transformada inversa

RC=R*C

RC_=5*RC

figure
bode(G)


