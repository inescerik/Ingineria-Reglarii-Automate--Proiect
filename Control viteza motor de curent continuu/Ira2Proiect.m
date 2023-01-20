close all
Hf=tf([0.46],[0.5 1])
Ho=feedback(Hf,1)

step(Ho)

% vreau ca timpu de raspns sa scada la 0.4
tr=0.4;
spr=0.05;
tita=abs(log(spr))/sqrt((log(spr)).^2+pi^2)
wn=4/(tr*tita)
cv=wn/(2*tita)
wb=wn*sqrt(1-2*tita^2+sqrt(2-4*tita^2+4*tita^4))
Ho2=tf([wn^2],[1 2*tita*wn wn^2])

figure
step(Ho2)

Hr=1/Hf*(Ho2/(1-Ho2));
Hr=minreal(Hr)


% H0=minreal(feedback(Hf*Hr,1))
%de la hr am luat T=1/20 => Te=0.025;
Te=0.025;
Hzoh=c2d(Ho2,Te,'zoh')

figure
step(Hzoh)

Hr_zoh=c2d(Hr,Te,'zoh')
step(feedback(Hr_zoh*c2d(Hf,Te,'zoh'),1))
