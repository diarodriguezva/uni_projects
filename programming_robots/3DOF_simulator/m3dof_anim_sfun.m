function [sys,x0,str,ts] = m3dof_anim_sfun(t,x,u,flag,Ts0,al,eg,tl)
persistent p1 p2 p3 p4 p5 p6 p7 p8 p9 f fd;
switch flag
    case 0
        sizes = simsizes;
        sizes.NumContStates = 0;
        sizes.NumDiscStates = 0;
        sizes.NumOutputs = 0;
        sizes.NumInputs = 16;
        sizes.DirFeedthrough = 16;
        sizes.NumSampleTimes = 1;
        ts = [Ts0 0];
        sys = simsizes(sizes);
        x0 = [];
        str = [];
        f = [];
        fd = [];
        if isempty(get(0,'CurrentFigure'))
            %al = 2;
            figure('Resize','on','NumberTitle','on');
            hold on;
            
            p4 = plot(0,0,':k','LineWidth',1,'Erasemode','xor');            % actual position        
            p5 = plot([0 0],[0 0],'r','Erasemode','xor');                   % actual orientiation (x-axis)
            p6 = plot([0 0],[0 0],'g','Erasemode','xor');                   % actual orientiation (y-axis)
            p7 = plot(0,0,'-k','LineWidth',1,'Erasemode','xor');            % desired postion
            p8 = plot([0 0],[0 0],'r','Erasemode','xor');                   % desired orientiation (x-axis)
            p9 = plot([0 0],[0 0],'g','Erasemode','xor');                   % desired orientiation (y-axis)
            
            p1 = plot([0 0],[0 0],'-b','LineWidth',3,'Erasemode','xor');    % link 1
            p2 = plot([0 0],[0 0],'-c','LineWidth',3,'Erasemode','xor');    % link 2
            p3 = plot([0 0],[0 0],'-b','LineWidth',3,'Erasemode','xor');    % link 3
            
            plot([0 1]*0.1*al,[0 0]*0.1*al,'r');                            % base frame (x-axis)
            plot([0 0]*0.1*al,[0 1]*0.1*al,'g');                            % base frame (y-axis)
            
            egx = [-al+0.1*al,-al+0.1*al-eg(1)*0.1*al];
            egy = [al-0.1*al,al-0.1*al-eg(2)*0.1*al];
            plot(egx,egy/9.8,'-');                                              % gravity direction
            if -eg(1)>0
                pfeil = '>';
            end
            if -eg(1)<0
                pfeil = '>';
            end
            if -eg(2)>0
                pfeil = '^';
            end
            if -eg(2)<0
                pfeil = 'v';
            end
            plot(egx(2),egy(2)/9.8,pfeil,'MarkerFaceColor','b');                % gravity direction
            text(-al+0.2*al,(al-0.2*al)/9.8,'G');                                 % gravity direction
            
            hold off;
            axis equal; axis off;
            set(gca,'Drawmode','Fast','NextPlot','ReplaceChildren');
            axis([-al al -al al]);
            xlabel('x'); ylabel('y');
        else
            %al = 2;
            hfg = get(0,'CurrentFigure');
            clf(hfg);
            set(0,'CurrentFigure',hfg);
            set(hfg,'Resize','on','NumberTitle','on');
            hold on;
            
            p4 = plot(0,0,':k','LineWidth',1,'Erasemode','xor');            % actual position        
            p5 = plot([0 0],[0 0],'r','Erasemode','xor');                   % actual orientiation (x-axis)
            p6 = plot([0 0],[0 0],'g','Erasemode','xor');                   % actual orientiation (y-axis)
            p7 = plot(0,0,'-k','LineWidth',1,'Erasemode','xor');            % desired postion
            p8 = plot([0 0],[0 0],'r','Erasemode','xor');                   % desired orientiation (x-axis)
            p9 = plot([0 0],[0 0],'g','Erasemode','xor');                   % desired orientiation (y-axis)
            
            p1 = plot([0 0],[0 0],'-b','LineWidth',3,'Erasemode','xor');    % link 1
            p2 = plot([0 0],[0 0],'-c','LineWidth',3,'Erasemode','xor');    % link 2
            p3 = plot([0 0],[0 0],'-b','LineWidth',3,'Erasemode','xor');    % link 3
            
            plot([0 1]*0.1*al,[0 0]*0.1*al,'r');                            % base frame (x-axis)
            plot([0 0]*0.1*al,[0 1]*0.1*al,'g');                            % base frame (y-axis)
            
            egx = [-al+0.1*al,-al+0.1*al-eg(1)*0.1*al];
            egy = [al-0.1*al,al-0.1*al-eg(2)*0.1*al];
            plot(egx,egy,'-');                                              % gravity direction
            if -eg(1)>0
                pfeil = '>';
            end
            if -eg(1)<0
                pfeil = '>';
            end
            if -eg(2)>0
                pfeil = '^';
            end
            if -eg(2)<0
                pfeil = 'v';
            end
            plot(egx(2),egy(2),pfeil,'MarkerFaceColor','b');                % gravity direction
            text(-al+0.2*al,al-0.2*al,'G');                                 % gravity direction
            
            hold off;
            axis equal; axis off;
            set(gca,'Drawmode','Fast','NextPlot','ReplaceChildren');
            axis([-al al -al al]);
            xlabel('x'); ylabel('y');
        end
        
    case 3
        set(p1,'xdata',[0 u(1)],'ydata',[0 u(2)]);
        set(p2,'xdata',[u(1) u(3)],'ydata',[u(2) u(4)]);
        set(p3,'xdata',[u(3) u(5)],'ydata',[u(4) u(6)]);
        if isempty(f)
            f = [ones(tl,1)*u(5) ones(tl,1)*u(6)];
        end
        f = [f(2:(size(f,1)),:);u(5) u(6)];
        set(p4,'xdata',f(:,1),'ydata',f(:,2));
        R = [u(7) u(8);u(9) u(10)]';
        XA = [u(5) u(6);(0.1*al*R*[1;0])'+[u(5) u(6)]];
        YA = [u(5) u(6);(0.1*al*R*[0;1])'+[u(5) u(6)]];
        set(p5,'xdata',XA(:,1),'ydata',XA(:,2));
        set(p6,'xdata',YA(:,1),'ydata',YA(:,2));
        if isempty(fd)
            fd = [ones(tl,1)*u(5) ones(tl,1)*u(6)];
        end
        fd = [fd(2:(size(fd,1)),:);u(11) u(12)];
        set(p7,'xdata',fd(:,1),'ydata',fd(:,2));
        Rd = [u(13) u(14);u(15) u(16)]';
        XAd = [u(11) u(12);(0.1*al*Rd*[1;0])'+[u(11) u(12)]];
        YAd = [u(11) u(12);(0.1*al*Rd*[0;1])'+[u(11) u(12)]];
        set(p8,'xdata',XAd(:,1),'ydata',XAd(:,2));
        set(p9,'xdata',YAd(:,1),'ydata',YAd(:,2));

        drawnow;
end