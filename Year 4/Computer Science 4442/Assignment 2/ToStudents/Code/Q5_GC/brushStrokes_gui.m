


function varargout = brushStrokes_gui(varargin)
% brushStrokes_gui MATLAB code for brushStrokes_gui.fig
%      brushStrokes_gui, by itself, creates a new brushStrokes_gui or raises the existing
%      singleton*.
%
%      H = brushStrokes_gui returns the handle to a new brushStrokes_gui or the handle to
%      the existing singleton*.
%
%      brushStrokes_gui('CALLBACK',hObject,eventData,handles,...) calls the local
%      function named CALLBACK in brushStrokes_gui.M with the given input arguments.
%
%      brushStrokes_gui('Property','Value',...) creates a new brushStrokes_gui or raises the
%      existing singleton*.  Starting from the left, property value pairs are
%      applied to the myGui before brushStrokes_gui_OpeningFcn gets called.  An
%      unrecognized property name or invalid value makes property application
%      stop.  All inputs are passed to brushStrokes_gui_OpeningFcn via varargin.
%
%      *See myGui Options on GUIDE's Tools menu.  Choose "myGui allows only one
%      instance to run (singleton)".
%
% See also: GUIDE, GUIDATA, GUIHANDLES

% Edit the above text to modify the response to help HistoSeg_Gui

% Last Modified by GUIDE v2.5 26-Feb-2014 10:19:19

% Begin initialization code - DO NOT EDIT
gui_Singleton = 1;
gui_State = struct('gui_Name',       mfilename, ...
                   'gui_Singleton',  gui_Singleton, ...
                   'gui_OpeningFcn', @brushStrokes_gui_OpeningFcn, ...
                   'gui_OutputFcn',  @brushStrokes_gui_OutputFcn, ...
                   'gui_LayoutFcn',  [] , ...
                   'gui_Callback',   []);
if nargin && ischar(varargin{1})
    gui_State.gui_Callback = str2func(varargin{1});
end

if nargout
    [varargout{1:nargout}] = gui_mainfcn(gui_State, varargin{:});
else
    gui_mainfcn(gui_State, varargin{:});
end
% End initialization code - DO NOT EDIT


% --- Executes just before brushStrokes_gui is made visible.
function brushStrokes_gui_OpeningFcn(hObject, eventdata, handles, varargin)
% This function has no output args, see OutputFcn.
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% varargin   command line arguments to HistoSeg_Gui (see VARARGIN)

% Choose default command line output for HistoSeg_Gui
handles.output = hObject;
handles.scribbleColors =[1 0 0; 0 0 1]; % scribble colors: 
handles.scribbleColorId = 1;
set(handles.pushbutton_object1, 'BackgroundColor', handles.scribbleColors(1, :));
set(handles.pushbutton_object2, 'BackgroundColor', handles.scribbleColors(2, :));


handles.mouseDown = false;
handles.img = [];
handles.scribbleMask = [];
handles.scribbleImg = [];
handles.loadedFlag = false;
set(handles.popupmenuRadius,'Value',2);
handles.radiusId = get(handles.popupmenuRadius,'Value');
handles.radiusNames = get(handles.popupmenuRadius, 'String');
handles.currMask = zeros(size(handles.img,1),size(handles.img,2));
% adjust buttons to be enabled/disabled
% enable clear curr stroke buttons if there are strokes
adjustClearCurrStrokeButton(hObject, handles);
% check whether clear all stroke is enabled
adjustClearAllStrokesButton(hObject, handles);
% check whether segment is enabled (there are at least one fg and one bg stroke)
adjustSegmentButton(hObject,handles);
% check whether saveData is enabled (there is scribbles cell array)
adjustSaveDataButton(hObject,handles);



% Update handles structure
guidata(hObject, handles);

% UIWAIT makes brushStrokes_gui wait for user response (see UIRESUME)
% uiwait(handles.myGui);


% --- Outputs from this function are returned to the command line.
function varargout = brushStrokes_gui_OutputFcn(hObject, eventdata, handles) 
% varargout  cell array for returning output args (see VARARGOUT);
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Get default command line output from handles structure
varargout{1} = handles.output;


% --- Executes on button press in pushbuttonLoadImg.
function pushbuttonLoadImg_Callback(hObject, eventdata, handles)
% hObject    handle to pushbuttonLoadImg (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
[filename, pathname] = uigetfile( ...
    {'*.jpg;*.jpeg;*.png;*.tiff;*.tif;*.bmp','All Images (*jpg,*.jpeg,*.png,*.tiff,*.tif,*.bmp)'; ...
     '*.jpg;*.jpeg',       'JPEG Files (*.jpg,*.jpeg)'; ...
     '*.png;',             'PNG files (*.png)'; ...
     '*.tiff;*.tif',            'TIFF files (*.tiff,*.tif)';...
     '*.bmp;*.bmp',            'BMP files (*.bmp)';...
     '*.*',                'All files (*.*)';}, ...
     'Load image','.\');

 if isequal(filename,0)
   disp('User selected Cancel')
 else
 
    filename = [pathname filename];

%     if (exist(filename,'file')~=0)
    
    disp('Loading New Image...');
    loadNewImage(hObject,handles,filename);
end

function loadNewImage(hObject,handles,filename)
% load the image
tempImg = double(imread(filename))/255;
% tempImg = imresize(tempImg,0.5);
tempImg(tempImg>1) = 1;
tempImg(tempImg<0) = 0;

handles.img = tempImg;%expect values between 0 and 255

% create scribble mask
handles.scribbleMask  = zeros(size(handles.img,1),size(handles.img,2));
handles.scribbleImg = handles.img;
handles.loadedFlag = true;
% prepare the axes for displaying new image with replace mode
set(handles.axesImg,'NextPlot','replace');
set(handles.axesImg,'Visible','on');
set(gcf,'CurrentAxes',handles.axesImg);
% show the image
imshow(handles.img); impixelinfo;
% prepare the axes for scribbling with add mode
set(handles.axesImg,'NextPlot','add');
% adjust buttons to be enabled/disabled
% enable clear curr stroke buttons if there are strokes
adjustClearCurrStrokeButton(hObject, handles);
% check whether clear all stroke is enabled
adjustClearAllStrokesButton(hObject, handles);
% check whether segment is enabled (there are at least one fg and one bg stroke)
adjustSegmentButton(hObject,handles);
% check whether saveData is enabled (there is scribbles cell array)
adjustSaveDataButton(hObject,handles);

% update the handles
guidata(gcbo, handles);

% --- Executes on button press in pushbuttonLoadData.
function pushbuttonLoadData_Callback(hObject, eventdata, handles)
% hObject    handle to pushbuttonLoadData (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
[filename, pathname] = uigetfile( ...
    {'*.mat','Matlab Data'; ...
     '*.*',                'All files (*.*)'}, ...
     'Load Data','.\');

if isequal(filename,0)
   disp('User selected Cancel');
else
    filename = [pathname filename];
%     if (exist(filename,'file'))
    loadNewData(hObject,handles,filename);
end


% Update handles structure
% guidata(hObject, handles);



% --- Executes on button press in pushbuttonSaveData.
function pushbuttonSaveData_Callback(hObject, eventdata, handles)
% hObject    handle to pushbuttonSaveData (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
[filename, pathname] = uiputfile( ...
    {'*.mat','Matlab Data (*.mat)'; ...
     '*.*',                'All files (*.*)'}, ...
     'Save Data','D:\Users\lgorelick\code\data');
 

 if isequal(filename,0) || isequal(pathname,0)
     disp('User pressed cancel')
 else
     img                         = handles.img;
     scribbleMask               = handles.scribbleMask;
     scribbleImg                 = handles.scribbleImg;
     paramsFileName = get(handles.edit_paramsGuiFilename,'String');
     filename = [pathname filename];     
     save(filename,...
         'img','scribbleMask','scribbleImg','paramsFileName');
 end

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function handles = loadNewData(hObject,handles,filename)
load(filename,...
    'img', 'scribbleMask','scribbleImg','paramsFileName');
% load(filename,...
%     'img', 'scribbleMask','scribbleImg',  'pSizes', 'segmentationMask');
% 

    
    handles.img                 = img;
    handles.scribbleMask        = scribbleMask;
    handles.scribbleImg         = scribbleImg;
    handles.currMask = zeros(size(handles.img,1),size(handles.img,2));
    set(handles.edit_paramsGuiFilename,'String',paramsFileName);
    
    % prepare the axes for displaying new image with replace mode
    set(handles.axesImg,'NextPlot','replace');
    set(handles.axesImg,'Visible','on');
    set(gcf,'CurrentAxes',handles.axesImg);
    % show the image
    imshow(handles.scribbleImg); impixelinfo;
    % prepare the axes for scribbling with add mode
    set(handles.axesImg,'NextPlot','add');
    handles.loadedFlag = true;
    
    % showSegmentationResults(img, segmentationMask, segmentationProbs,  scribbleMask, handles.scribbleColors);
    % adjust buttons to be enabled/disabled
    % enable clear curr stroke buttons if there are strokes
    adjustClearCurrStrokeButton(hObject, handles);
    % check whether clear all stroke is enabled
    adjustClearAllStrokesButton(hObject, handles);
    % check whether segment is enabled (there are at least one fg and one bg stroke)
    adjustSegmentButton(hObject,handles);
    % check whether saveData is enabled (there is scribbles cell array)
    adjustSaveDataButton(hObject,handles);
    
    
    guidata(hObject,handles);

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%






% --- Executes on button press in pushbuttonClearAllStrokes.
function pushbuttonClearAllStrokes_Callback(hObject, eventdata, handles)
% hObject    handle to pushbuttonClearAllStrokes (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

handles.scribbleMask(:) = 0;
handles.scribbleImg = handles.img;
set(gcf,'CurrentAxes',handles.axesImg);
imshow(handles.scribbleImg); impixelinfo;
set(handles.axesImg,'NextPlot','add');
% adjust buttons to be enabled/disabled
adjustClearCurrStrokeButton(hObject, handles);
adjustClearAllStrokesButton(hObject, handles);
adjustSegmentButton(hObject, handles);

% update the handles
guidata(gcbo, handles);

% --- Executes on button press in pushbuttonClearCurrStroke.
function pushbuttonClearCurrStroke_Callback(hObject, eventdata, handles)
% hObject    handle to pushbuttonClearCurrStroke (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% unscribble the image for the curr stroke
idx = (handles.scribbleMask == handles.scribbleColorId);

handles.scribbleMask(idx) = 0;
% paint with the color of orig image
handles.scribbleImg(idx(:,:,[1 1 1])) = handles.img(idx(:,:,[1 1 1]));

set(gcf,'CurrentAxes',handles.axesImg);
imshow(handles.scribbleImg); impixelinfo;
set(handles.axesImg,'NextPlot','add');

% adjust button to be enabled/disabled
adjustClearCurrStrokeButton(hObject, handles);
adjustClearAllStrokesButton(hObject, handles);
adjustSegmentButton(hObject, handles);

% update the handles
guidata(gcbo, handles);





% --- Executes on selection change in popupmenuRadius.
function popupmenuRadius_Callback(hObject, eventdata, handles)
% hObject    handle to popupmenuRadius (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: contents = cellstr(get(hObject,'String')) returns popupmenuRadius contents as cell array
%        contents{get(hObject,'Value')} returns selected item from popupmenuRadius

handles.radiusId = get(handles.popupmenuRadius,'Value');
handles.radiusNames = get(handles.popupmenuRadius, 'String');

% Update handles structure
guidata(hObject, handles);

% --- Executes during object creation, after setting all properties.
function popupmenuRadius_CreateFcn(hObject, eventdata, handles)
% hObject    handle to popupmenuRadius (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: popupmenu controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



% --- Executes on mouse press over figure background, over a disabled or
% --- inactive control, or over an axes background.
function myGui_WindowButtonDownFcn(hObject, eventdata, handles)
handles.mouseDown = true;
handles.currMask = zeros(size(handles.img,1),size(handles.img,2));
    
guidata(hObject, handles);

% hObject    handle to myGui (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% --- Executes on mouse press over figure background, over a disabled or
% --- inactive control, or over an axes background.
function myGui_WindowButtonUpFcn(hObject, eventdata, handles)
handles.mouseDown = false;
set(handles.axesImg,'NextPlot','replace');

% add curr scribble to the scribbled image from the currMask

    % scribble on the image with the correct color
    idx = find(handles.currMask == handles.scribbleColorId);
    handles.scribbleImg(idx)         = handles.scribbleColors(handles.scribbleColorId,1);
    handles.scribbleImg(idx+size(handles.img,1)*size(handles.img,2))   = handles.scribbleColors(handles.scribbleColorId,2);
    handles.scribbleImg(idx+2*size(handles.img,1)*size(handles.img,2)) = handles.scribbleColors(handles.scribbleColorId,3);
    % scribble on the mask with the correct scribbleId
    handles.scribbleMask(idx) = handles.scribbleColorId;


% show the scribbleImg
set(gcf,'CurrentAxes',handles.axesImg);
imshow(handles.scribbleImg); impixelinfo;
set(handles.axesImg,'NextPlot','add');

% adjust buttons to be enabled/disabled
% enable clear curr stroke buttons if there are strokes
adjustClearCurrStrokeButton(hObject, handles);
% check whether clear all stroke is enabled
adjustClearAllStrokesButton(hObject, handles);
% check whether segment is enabled (there are at least one fg and one bg stroke)
adjustSegmentButton(hObject,handles);

guidata(hObject, handles);


% hObject    handle to myGui (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% --- Executes on mouse motion over figure - except title and menu.
function myGui_WindowButtonMotionFcn(hObject, eventdata, handles)

% if we are moving with buttonDown
if handles.mouseDown
        
    % get position relative to the axes
    currentPoint = get(handles.axesImg,'CurrentPoint');
    currentPoint = round(currentPoint(1,[2 1]));
%     maxPsize = max(handles.pSizes);
    currRadius = str2double(handles.radiusNames(handles.radiusId));
    
    if (currentPoint(1) <= (size(handles.img,1) - currRadius - 2)) && (currentPoint(1) > currRadius + 2) && ...
            (currentPoint(2) <= (size(handles.img,2)- currRadius - 2)) && (currentPoint(2) > currRadius + 2)
        
        % get mask of a circle around currPoint
        circleMask = getCircle(currentPoint, str2double(handles.radiusNames(handles.radiusId)), [size(handles.img,1) size(handles.img,2)]);
        
        % label based on the color chosen
        handles.currMask(circleMask) = handles.scribbleColorId;
        
        % plot current motion
        [i j v] = find(circleMask);
        position = get(handles.axesImg,'Position'); % in points
        pixelsPerPoint = size(handles.img,1)/position(4);
        scatter(handles.axesImg,currentPoint(2),currentPoint(1), pi * ((str2double(handles.radiusNames(handles.radiusId))+1)/pixelsPerPoint).^2,'filled','MarkerFaceColor',handles.scribbleColors(handles.scribbleColorId,:));
        %     plot(handles.axesImg,currentPoint(2),currentPoint(1),  'MarkerSize', pi * str2double(handles.radiusNames(handles.radiusId)).^2,'MarkerFaceColor',handles.scribbleColors(handles.scribbleColorId,:),'Marker','o');
        
    end
    guidata(hObject, handles);
end
% hObject    handle to myGui (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)





% checks whether there is stroke for current color and enables/disables
% accordingly the button
function adjustClearCurrStrokeButton(hObject, handles)
% enable clear curr stroke button
if  nnz(handles.scribbleMask == handles.scribbleColorId)
    set(handles.pushbuttonClearCurrStroke,'enable','on');
else
    set(handles.pushbuttonClearCurrStroke,'enable','off');
end

guidata(hObject, handles);

% checks whether there is at least one stroke of any color and enables/disables
% accordingly the button
function adjustClearAllStrokesButton(hObject, handles)
if nnz(handles.scribbleMask)
    set(handles.pushbuttonClearAllStrokes,'enable','on');
else
    set(handles.pushbuttonClearAllStrokes,'enable','off');
end
guidata(hObject, handles);

% checks whether there are at least one stroke of each color
function adjustSegmentButton(hObject, handles)
if length(unique(handles.scribbleMask)) > 2 % there is always zero which is not a label
     set(handles.pushbuttonSegment,'enable','on');
else
     set(handles.pushbuttonSegment,'enable','off');
end
guidata(hObject, handles);

% checks whether there are models for scribble, meaning the segment button was pushed at least once 
function adjustSaveDataButton(hObject, handles)
if handles.loadedFlag
     set(handles.pushbuttonSaveData,'enable','on');
else
     set(handles.pushbuttonSaveData,'enable','off');
end
guidata(hObject, handles);

% --- Executes on button press in pushbutton_object1.
function pushbutton_object1_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton_object1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
handles.scribbleColorId = 1;
guidata(hObject, handles);

% --- Executes on button press in pushbutton_object2.
function pushbutton_object2_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton_object2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
handles.scribbleColorId = 2;
guidata(hObject, handles);



function edit_paramsGuiFilename_Callback(hObject, eventdata, handles)
% hObject    handle to edit_paramsGuiFilename (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit_paramsGuiFilename as text
%        str2double(get(hObject,'String')) returns contents of edit_paramsGuiFilename as a double


% --- Executes during object creation, after setting all properties.
function edit_paramsGuiFilename_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit_paramsGuiFilename (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes on button press in pushbutton_chooseParams.
function pushbutton_chooseParams_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton_chooseParams (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
[shortFilename, pathname] = uigetfile( ...
    {'*params*.m;','All Param Files (*params*.m)';}, ...
     'Load Parameters','.\');

 if isequal(shortFilename,0)
   disp('User selected Cancel')


 else
    filename = [pathname shortFilename];
%     if (exist(filename,'file')~=0)
    
    handles.paramsFilename = filename;
    set(handles.edit_paramsGuiFilename,'String',shortFilename);
end
guidata(hObject, handles);




%***************************************************************
%***************************************************************
% --- Executes on button press in pushbuttonSegment.
function pushbuttonSegment_Callback(hObject, eventdata, handles)
% hObject    handle to pushbuttonSegment (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
img = handles.img;
scribbleMask  = handles.scribbleMask;
paramsFileName = get(handles.edit_paramsGuiFilename,'String');
% read parameters from the params file
run( paramsFileName(1:end-2) );
f_result = figure;


[segm] = segmentGC_internal(img*255,scribbleMask);


foreground = double(img*255);

R = foreground(:,:,1);
G = foreground(:,:,2);
B = foreground(:,:,3);

foreground = cat(3,R.*segm,G.*segm,B.*segm);

%imwrite(uint8(foreground),'f.png');

imagesc(uint8(foreground));

%%% run your function that uses the scribble the image and the parameters:
%%% resultImg = yourFunction(img, scribbleMask, param1, param2 ...)
%%% figure(f_result);
%%% imagesc(result); axis image, axis off; impixelinfo
%%%


% adjust the save data button to be enabled
adjustSaveDataButton(hObject, handles);

guidata(hObject, handles);

