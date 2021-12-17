clc;
clear;
NN=[50,100,200];
r0=2;%bps/Hz

%% location of every node
loc_S=[0,0];
loc_D=[100,0];
loc_I=[50,10];
loc_R=[50,0];
d_SR=sqrt((loc_S(1)-loc_R(1))^2+(loc_S(2)-loc_R(2))^2);
d_SI=sqrt((loc_S(1)-loc_I(1))^2+(loc_S(2)-loc_I(2))^2);
d_IR=sqrt((loc_I(1)-loc_R(1))^2+(loc_I(2)-loc_R(2))^2);
d_RI=d_IR;
d_RD=sqrt((loc_R(1)-loc_D(1))^2+(loc_R(2)-loc_D(2))^2);
d_ID=sqrt((loc_I(1)-loc_D(1))^2+(loc_I(2)-loc_D(2))^2);

Rician_factor=10;%Rician_K factor(dB);
alpha=[2,2.5];%express the path-loss exponent of rayleigh channel and racian channel represpectly.
eta=0.8;
zeta=0.8;
miu=0.8;

low=15;%dB
high=60;%dB
Np=17;
SNR=linspace(low,high,Np);%SNR=P/(σ_ω)2
R_sim_only_IRS=zeros(length(NN),Np);
monte_carlo=1e4;
R_sim_temp=zeros(1,monte_carlo);
for n=1:length(NN)
    N=NN(n);
    for i=1:Np
        snr=10^(SNR(i)/10);
        for j=1:monte_carlo
            %% simulate channel state information
            h_SI=1/sqrt(2)*d_SI^(-alpha(2)/2)*complex(randn(1,N),randn(1,N));
            h_ID=1/sqrt(2)*d_ID^(-alpha(2)/2)*complex(randn(1,N),randn(1,N));
            
            channel_gain_SID=miu*sum(abs(h_SI.*h_ID));
            R_sim_temp(j)=log2(1+snr*channel_gain_SID^2);
        end
        R_sim_only_IRS(n,i)=mean(R_sim_temp);
    end
end
plot(SNR,R_sim_only_IRS(1,:),'--k',SNR,R_sim_only_IRS(2,:),'--k',SNR,R_sim_only_IRS(3,:),'--k','Linewidth',2)
xlabel('SNR(dB)');
ylabel('Achievable rate(bps/Hz)');
%axis([low,high,0,6]);
legend('IRS only(Sim.)_N_l_o_s','Location','northwest');
grid on;
hold on;