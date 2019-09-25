


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

% Last Modified by GUIDE v2.5 10-Jan-2017 14:24:17

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
handles.scribbleColors =[1; 0]; % scribble colors: 
handles.scatterPlotColors =[[1 1 1]; [0 0 0]]; % scribble colors: 
handles.scribbleColorId = 1;
set(handles.pushbutton_object1, 'BackgroundColor', [1 1 1]);
set(handles.pushbutton_object2, 'BackgroundColor', [0 0 0]);
set(handles.uipanel_bg,'visible','off');
set(handles.pushbuttonSaveData,'enable','on');



handles.mouseDown = false;
handles.img = zeros(28);
handles.scribbleMask = zeros(28);
handles.scribbleImg = zeros(28);
set(handles.popupmenuRadius,'Value',1);
handles.radiusId = get(handles.popupmenuRadius,'Value');
handles.radiusNames = get(handles.popupmenuRadius, 'String');

handles.currMask = zeros(28);
handles.myData = load('myData.mat');

loadNewImage(hObject,handles);
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

    loadNewImage(hObject,handles);


function loadNewImage(hObject,handles)
handles.mouseDown = false;
handles.img = zeros(28);
handles.scribbleMask = zeros(28);
handles.scribbleImg = zeros(28);
set(handles.popupmenuRadius,'Value',1);
handles.radiusId = get(handles.popupmenuRadius,'Value');
handles.radiusNames = get(handles.popupmenuRadius, 'String');

handles.currMask = zeros(28);
% prepare the axes for displaying new image with replace mode
set(handles.axesImg,'NextPlot','replace');
set(handles.axesImg,'Visible','on');
set(gcf,'CurrentAxes',handles.axesImg);
% show the image
imshow(handles.img); impixelinfo;
% prepare the axes for scribbling with add mode
set(handles.axesImg,'NextPlot','add');

set(handles.edit_label,'String','?')

% update the handles
guidata(hObject, handles);



% --- Executes on button press in pushbuttonSaveData.
function pushbuttonSaveData_Callback(hObject, eventdata, handles)
% hObject    handle to pushbuttonSaveData (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
[filename, pathname] = uiputfile( ...
    {'myDigit.bmp'}, ...
     'Save Image');
 

 if isequal(filename,0) || isequal(pathname,0)
     disp('User pressed cancel')
 else
        
     
     filename = [pathname filename];     
     imwrite(handles.scribbleImg,filename); 
 end



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

% scribble on the image with the correct color
idx = find(handles.currMask == handles.scribbleColorId);

% add curr scribble to the scribbled image from the currMask
handles.scribbleImg(idx)         = handles.scribbleColors(handles.scribbleColorId,1);
% scribble on the mask with the correct scribbleId
handles.scribbleMask(idx) = handles.scribbleColorId;


% show the scribbleImg
set(gcf,'CurrentAxes',handles.axesImg);
imshow(handles.scribbleImg); impixelinfo;
set(handles.axesImg,'NextPlot','add');

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
        circleMask = getCircle(currentPoint, currRadius, [size(handles.img,1) size(handles.img,2)]);
        
        % label based on the color chosen
        handles.currMask(circleMask) = handles.scribbleColorId;
        
        % plot current motion
        [i j v] = find(circleMask);
        position = get(handles.axesImg,'Position'); % in points
        pixelsPerPoint = size(handles.img,1)/position(4);
        
        scatter(handles.axesImg,currentPoint(2),currentPoint(1),0.6* pi * ((currRadius+1)/pixelsPerPoint).^2,'filled','MarkerFaceColor',handles.scatterPlotColors(handles.scribbleColorId,:));

    end
    guidata(hObject, handles);
end
% hObject    handle to myGui (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


%***************************************************************
%***************************************************************
% --- Executes on button press in pushbuttonSegment.
function pushbuttonSegment_Callback(hObject, eventdata, handles)
% hObject    handle to pushbuttonSegment (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
 

img = handles.scribbleImg;

myData = load('myData.mat');
handles.myData = myData;

%myData = handles.myData;


img = imresize(img,[16,16]);
label = recognize_digit(img(:), myData);

set(handles.edit_label,'String', num2str(label));



guidata(hObject, handles);


function pushbutton_object2_Callback(hObject, eventdata, handles)
% hObject    handle to pushbuttonSegment (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

handles. scribbleColorId = 2;
set(handles.uipanel_bg,'visible','on');
set(handles.uipanel_fg,'visible','off');
set(handles.pushbutton_object2,'visible','on')
set(handles.pushbutton_object1,'visible','on')
guidata(hObject, handles);


function pushbutton_object1_Callback(hObject, eventdata, handles)
% hObject    handle to pushbuttonSegment (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

handles. scribbleColorId = 1;
set(handles.uipanel_bg,'visible','off');
set(handles.uipanel_fg,'visible','on');
set(handles.pushbutton_object2,'visible','on')
set(handles.pushbutton_object1,'visible','on')


guidata(hObject, handles);



function edit_label_Callback(hObject, eventdata, handles)
% hObject    handle to edit_label (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit_label as text
%        str2double(get(hObject,'String')) returns contents of edit_label as a double


% --- Executes during object creation, after setting all properties.
function edit_label_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit_label (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end
