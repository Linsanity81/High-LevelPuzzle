obj_files = getFiles "*.obj"

tmpidcnt = 0

timing = 0

ActionID = 0

for f in obj_files do 
(
	if ( doesfileexist f ) do
		importFile f #noPrompt using:Wavefront_Object 
	
	objfilename = getFilenameFile f
	
	for geo in geometry 
		where ((geo.name == objfilename) or (matchPattern geo.name pattern:"3D_Object*") or (matchPattern geo.name pattern:"default*") or (matchPattern geo.name pattern:"*_obj")) do 
	(
		--geo.name = (f as string) 
		pathaa = filterString (f as string) "\\"
		geo.name = pathaa[pathaa.count]
		
		tmpidcnt += 1
		
		geo.colorByLayer = false
		
		geo.pivot = [0,0,0]
		--addModifier geo (smooth())
		--geo.smooth.autosmooth =true
					
		addModifier geo (unwrap_UVW())
					
		convertToMesh geo
			
					-- weld vertex within 0.001 distance
		--meshop.weldVertsByThreshold geo #{1..geo.numverts} 0.0001
					
		----------------------------------------------------------------
		-- Use the smooth shaded rendering style
					
		-- smooth the normal
		addModifier geo (smooth())
		geo.smooth.autosmooth = false
		geo.smooth.threshold  = 40
					
		----------------------------------------------------------------
		-- Use the flat shaded rendering style
					
		addModifier geo (Edit_Normals())
			
		geo.Edit_Normals.displayLength = 0.0
		geo.Edit_Normals.AverageGlobal useThresh:on threshold:0.001
					
		-- Select all the normals
		num = geo.Edit_Normals.GetNumNormals()
		selectedNormals = #{1..num}
		geo.Edit_Normals.SetSelection selectedNormals
				
		-- Apply the break operator
		geo.Edit_Normals.Break()
				
		-- Deselect the normals
		geo.Edit_Normals.SetSelection #{}
		
		-- Set material color for all the pieces	
		newMat = case tmpidcnt of
				(
					1:  compositematerial basematerial:(standard diffuse:(color 150 237 151))
					2:  compositematerial basematerial:(standard diffuse:(color 139 239 239))
					3:  compositematerial basematerial:(standard diffuse:(color 192 139 237))
					4:  compositematerial basematerial:(standard diffuse:(color 237 237 149))
					5:  compositematerial basematerial:(standard diffuse:(color 149 149 237))
					6:  compositematerial basematerial:(standard diffuse:(color 255 149 213))
					7:  compositematerial basematerial:(standard diffuse:(color 171 139 124))
					8:  compositematerial basematerial:(standard diffuse:(color 215 254 130))
					9:  compositematerial basematerial:(standard diffuse:(color 200 200 220))
					10: compositematerial basematerial:(standard diffuse:(color 197 160 178))
					default: compositematerial basematerial:(standard diffuse:(random white black))
				)
					
		geo.material = newMat
				
		-- Render black wireframe
		--geo.material.materiallist[3] = standardMat
		geo.material.materiallist[2] = standard wire:on diffuse:(color 30 30 30)
				
		-- geo.visibility = 1
		--matName = "WOOD" + (((mod tmpidcnt 12)+1 as interger) as string)
		--geo.material = currentMaterialLibrary[matName] -- add material
	)
)

-- Load the obj file names
xmlDoc = dotNetObject "system.xml.xmlDocument"

xmlDoc.load "animation.motion.xml"

docEle=xmlDoc.documentElement

pieceNumStr = docEle.getattribute "Objects_num"

format "#Objects = %\n" pieceNumStr

-- Action
actionNodes = xmlDoc.selectNodes "//action"

for i = 0 to actionNodes.count - 1 do
(
	action = actionNodes.item[i]
	
	ActionID = ActionID + 1
	
	is_move = action.getattribute "is_move"

	x = action.getattribute "x"
	x_float = x as float

	y = action.getattribute "y"
	y_float = y as float

	z = action.getattribute "z"
	z_float = z as float

	movingVec = [0,0,0]
	movingVec.x = x_float
	movingVec.y = -z_float
	movingVec.z = y_float

	format "movingVec = %\n" movingVec

	frame = action.getattribute "frameNum"
	frameCnt = frame as float
	
	time1 = timing  --key start time
	time2 = timing + frameCnt  --key end time
	time3 = time2 + frameCnt 
	format "time1:%\n" time1
	format "time2:%\n" time2
	format "time3:%\n" time3
	
	pieceNodes = action.childNodes
	format "pieceCnt:%\n" pieceNodes.count 
	
	-- animation
	
	for j = 0 to pieceNodes.count - 1 do
	(
		currNode = pieceNodes.item[j]
		id = currNode.getattribute "id"
		currID = id as integer
		print id
		
		curObj = getNodeByName (obj_files[currID])
		curPosition = curObj.pos
		print("curPosition")
		print curPosition
		print("material")
		--print curObj.material.transparency
		
		
		if (is_move == "true") do
		(
			animate on 
			(
				at time time1	
				(
					curObj.pos = (at time time1 curObj.pos)
					curObj.material[1].opacity = 100
					curObj.material[2].opacity = 100
					--coPObj.pos = (at time time1 coPObj.pos)
					--currCloseUpLight.pos = (at time time1 currCloseUpLight.pos)
					--currCloseUpLight.target.pos = (at time time1 currCloseUpLight.target.pos)
								
				)
				at time time2 
				(
					curObj.pos = (at time time1 curObj.pos) + movingVec
					curObj.material[1].opacity = 100
					curObj.material[2].opacity = 100
					-- curObj.material[1].opacity = 0
					-- curObj.visibility = 0.5
					--coPObj.pos = (at time time1 coPObj.pos) + movingVec
					--currCloseUpLight.pos = (at time time1 currCloseUpLight.pos) + movingVec
					--currCloseUpLight.target.pos = (at time time1 currCloseUpLight.target.pos) + movingVec
								
				)	
			)
		)
		
		
		if (is_move == "false") do
		(
			animate on 
			(
				at time time1	
				(
					curObj.pos = (at time time1 curObj.pos)
					curObj.material[1].opacity = 100
					curObj.material[2].opacity = 100
					--curObj.material.transparency = 0
					--coPObj.pos = (at time time1 coPObj.pos)
					--currCloseUpLight.pos = (at time time1 currCloseUpLight.pos)
					--currCloseUpLight.target.pos = (at time time1 currCloseUpLight.target.pos)
							
							
				)
				at time time2 
				(
					curObj.pos = (at time time1 curObj.pos) + movingVec
					curObj.material[1].opacity = 100
					curObj.material[2].opacity = 100
					--curObj.material.transparency = 0
					--curObj.material.transparency = 1
					--coPObj.pos = (at time time1 coPObj.pos) + movingVec
					--currCloseUpLight.pos = (at time time1 currCloseUpLight.pos) + movingVec
					--currCloseUpLight.target.pos = (at time time1 currCloseUpLight.target.pos) + movingVec
							
				)	
				at time time3
				(
					--curObj.pos = (at time time2 curObj.pos) + 2 * movingVec
					curObj.material[1].opacity = 0
					curObj.material[2].opacity = 0
					--curObj.material.transparency = 1
					--coPObj.pos = (at time time1 coPObj.pos) + movingVec
					--currCloseUpLight.pos = (at time time1 currCloseUpLight.pos) + movingVec
					--currCloseUpLight.target.pos = (at time time1 currCloseUpLight.target.pos) + movingVec
							
				)	
			)
		)
	)
		timing += frameCnt 
)


