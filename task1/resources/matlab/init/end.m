% extract camera poses
camPoses = poses(vSet);

% plot camera poses.
plotCamera(camPoses, 'Size', 0.02);
hold on

% tea box
verts = ([0, 0.063, 0.093;
          0.165, 0.063, 0.093;
          0.165, 0, 0.093;
          0, 0, 0.093;
          0, 0.063, 0;
          0.165, 0.063, 0;
          0.165, 0, 0;
          0, 0, 0]);
face = [1 2 3 4;5 6 7 8;3 4 8 7;1 2 6 5;2 3 7 6;1 4 8 5];
h = patch('Faces', face, 'Vertices', verts, 'FaceColor', 'white', 'EdgeColor', 'black');
hold on

grid on
axis equal

% size
xlim([-0.7 0.7]);
ylim([-0.7 0.7]);
zlim([0 0.7]);

view(60,15);

title('Camera Poses');