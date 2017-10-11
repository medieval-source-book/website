/**
	* @license vmachine.js for VM 5.0
	* Updated: Aug 22 2015 by roman bleier
	* Adds JS functionality to VM 5.0
	* 
	* The document-ready statement executing jquery plugins is at the end of this script!
	* Some input comes from global variables added via the XSLT script - see settings.xsl and comments further below.
	*
	**/


function PanelInPosXY(selector, top, left){
	/** PanelInPosXY function to find if a panel/element is in the location left/top 
	*param selector: JQuery selector ( for instance to select all panels, or all visible panels)
	*param left: the left coordinates of the panel/element 
	*param top: the top coordinates of the panel/element
	*/
	panelPresent = false;
	$(selector).each(function(){
		var pos = $(this).position();
		if(pos.left == left && pos.top == top){
				panelPresent = true;
		}
	});
	return panelPresent;
}


$.fn.moveToFront = function() {
	/** moves panels (mssPanel, imgPanel, etc) to front. Adds a higher z-index**/
	var that = $(this);

	$(".activePanel").each(function(){
		$(this).css({"z-index":2}).removeClass("activePanel");
	});
    that.addClass("activePanel").css({"z-index":5, "opacity":1});

}

$.fn.panelResize = function (){
	var visiblePanels = $("div.panel:not(.imgPanel):not(.noDisplay)")
	var totalPanels = visiblePanels.length;
	var mssAreaWidth = $(this).width();
	var panelWidth = (mssAreaWidth / totalPanels) - 10;

	// resize every panel to fit width
	visiblePanels.each(function(idx, element) {
		$(element).width(panelWidth);
	});
}

/***** Functionality of dropdown menu and top menu *****/

$.fn.toggleOnOffButton = function() {
	/**
	*plugin toggles between ON and OFF status of a button of top menu and dropdown
	**/
	return $(this).each(function(){
    var b = $(this).find("span.toggle");
		var content = b.html();
		
		if (content === "ON"){
		    b.html("OFF");
		}
		if (content === "OFF"){
		    b.html("ON");
		}
		$(this).toggleClass("buttonPressed");
		});
	}

$.fn.versionMenu = function() {
	/**versionMenu plugin to add hover effect to the button #selectVersionButton
	* on hover the dropdown #versionList will be shown or hidden
	**/
    $(this).hover(function(){
        /* change visibility of the dropdown list, 
		statement 'ul#versionList.notVisible li{visibility: hidden;}' in css necessary 
		*/
		$("#versionList").removeClass('notVisible');
		$(this).find("img").toggleClass('noDisplay');
    },function(){
		$("#versionList").addClass('notVisible');
		$(this).find("img").toggleClass('noDisplay');
	});
	/* adds hovereffect on dropdown #versionList */
	$("#versionList").hover(function(){
			$(this).removeClass('notVisible');
		},function(){
			$(this).addClass('notVisible');
		}
	);
};

$.fn.linenumberOnOff = function() {
	/**plugin to add a click event to linenumberOnOff button
	*on click the line numbers in the panels become invisible
	**/
    return this.click(function(){
		$(".linenumber").toggleClass("noDisplay");
		var button = $("#linenumberOnOff");
		var text = button[0].childNodes[0].innerText;
        if (text.toUpperCase() == 'Line Numbers On'.toUpperCase()) {
			text = 'Line Numbers Off';
		} else {
			text = 'Line Numbers On';
		}
        button[0].childNodes[0].innerText = text;
	});
}

$.fn.panelButtonClick = function() {
	/**panelButtonClick plugin to control the click effect in the dropDownButton selectVersion
	*on click version panels become invisible or visible
	**/
    return this.click(function(){
		var dataPanelId = $(this).attr("data-panelid");

		if(dataPanelId === "notesPanel"){
			//toggle inline note icons in panels
			$("#mssArea .noteicon").toggle();
		}
		$("#"+dataPanelId).each(function(){
			var top = 0;
			var left = 0;
			$(this).changePanelVisibility(top, left);
			$(this).moveToFront();
		});
		$("#mssArea").panelResize();
		$("*[data-panelid='"+dataPanelId+"']").toggleOnOffButton();
	});
};
	
$.fn.panelButtonHover = function() {
	/**panelButtonHover plugin to add hover effect to the dropDownButton selectVersion
	*on hover corresponding version panels will be highlighted
	**/
    return this.hover(function(){
		/*mouse enter event*/
		var p = $(this).attr("data-panelid");
		$(this).addClass("highlight");
		$("#"+p).addClass("highlight");
	}, function(){
		/*mouse leave event*/
		var p = $(this).attr("data-panelid");
		
		$(this).removeClass("highlight");
		$("#"+p).removeClass("highlight");
		
	});	
};

/***** END Functionality of dropdown menu and top menu *****/

/***** Functionality and visibility of version, biblio, and note panels *****/

$.fn.changePanelVisibility = function(top,left) {
	/* plugin to change the visibility of a panel and move it to different location
	param top and left are the coordinates where the panel should be moved to*/
	$(this).toggleClass("noDisplay");
	if( top === "-1px" || top === -1){
		// top = $("#mainBanner").height();
		// Structure changed; should be at top of #mssArea
		top = 0;
	}
	else if( left === "-1px" || left === -1 ){
		left = 0;
	
	}

	if(!(top===undefined || left===undefined)){
	
		if($.type(top) === "string"){
			if((top.substr(-2) === "em") || (top.substr(-2) === "px")){
			top = top.slice(0,-2)
			}
		}
		if($.type(left) === "string"){
			if((left.substr(-2) === "em") || (left.substr(-2) === "px")){
				left = left.slice(0,-2)
			}
		}
		if(!isNaN(top) && !isNaN(left)){
			$(this).css({"left":left});
			$(this).css({"top":top});
		}
	}
}

$.fn.panelClick = function() {
	/** plugin to add a mousedown event to panels
	brings the panel to front
	**/
    return this.mousedown(function(){
		$(this).moveToFront();
	});
};

$.fn.panelHover = function() {
	/** plugin to add a hover event to panels
	on hover the class 'highlight' is added or removed
	**/
    return this.hover(function(){
			$(this).addClass("highlight");
			var p = $(this).attr("id");
			$(".dropdown li[data-panelid='"+p+"']").addClass("highlight");
		}, function(){
			$(this).removeClass("highlight");
			var p = $(this).attr("id");
			$(".dropdown li[data-panelid='"+p+"']").removeClass("highlight");
	});
};

$.fn.closeButtonClick = function() {
	/** plugin to add a click event to the closing button ('X') of panels 
	after a panel is closed the mssArea has to be resized
	**/
    return this.click(function(){
		var w = $(this).closest(".panel").attr("id");
		var panel = $(this).closest(".panel");
		
		if ( w === "notesPanel"){
			$(".noteicon").toggle();
		}		
		$(this).closest(".panel").addClass("noDisplay");
		$("*[data-panelid='"+w+"']").toggleOnOffButton();
		//$showNote.removeClass("clicked")
		$("#mssArea").panelResize();
		$(panel).find("audio").each(function(){
			$(this).trigger("pause");
			});
	});
};

/***** END Functionality and visibility of Version, Biblio, and Note panels *****/

/***** Functionality related to image panels *****/

$.fn.zoomPan = function() {
	/* plugin to use JQuery panzoom library for the image viewer
	https://github.com/timmywil/jquery.panzoom
	*/
	this.each(function(){
		var imgId = $(this).attr("id");
		var $section = $("div#" + imgId + ".imgPanel");
		$section.find('.panzoom').panzoom({
			$zoomIn: $section.find(".zoom-in"),
			$zoomOut: $section.find(".zoom-out"),
			$zoomRange: $section.find(".zoom-range")
		});
	});
};

$.fn.imgLinkClick = function() {
	/* plugin to add a click event to imgLinks (icons that open the image viewer on click) */
	this.click(function(e){
		var imgId = $(this).attr("data-img-id");
		var imagePanel = $("#"+imgId);
		imagePanel.appendTo("#mssArea");
		imagePanel.css({
			"position": "absolute",
			"top": e.pageY,
			"left": e.pageX - imagePanel.width(),
            "width": "30%",
            "height": "500px",
			}).toggleClass("noDisplay").addClass("activePanel");
		//move the image panel to the front of all visible panels
		imagePanel.moveToFront();
	});
};

$.fn.imgLinkHover = function() {
	/* plugin to add a hover event to imgLinks (icons that open the image viewer on click) */
	this.hover(function(){
	/* current hover event add class 'highlight' on hover*/
		$(this).addClass("highlight");
		$(this).css({"border":"1px solid red"});
		var panelId = $(this).attr("data-img-id");
		$(".imgPanel[id='" + panelId + "']").addClass("highlight");
	},function(){
	/* on hover out remove 'highlight' class*/
		$(this).removeClass("highlight");
		$(this).css({"border":"1px solid white"});
		var panelId = $(this).attr("data-img-id");
		$(".imgPanel[id='" + panelId + "']").removeClass("highlight");
	});
};

$.fn.imgPanelMousedown = function() {
	/* plugin to add a mousedown event to image panels */
    return this.mousedown(function(){
			$(this).moveToFront();
	});	
};
$.fn.imgPanelHover = function() {
	/* plugin to add a hover event to the image panels*/
    return this.hover(function(){
			var imageId = $(this).attr("id");
			$("img[data-img-id='" + imageId +"']").css({"border":"1px solid red"});
			$(this).addClass("highlight");
		}, function(){
			var imageId = $(this).attr("id");
			$("img[data-img-id='" + imageId +"']").css({"border":"1px solid white"});
			$(this).removeClass("highlight");
		});
};
/***** END Functionality related to image panels *****/

/***** Functionality popup notes *****/

$.fn.clickPopupNote = function() {
	/*** plugin to add a click effect and popup note ***/
	var noteIcon = this;	
	//"div.noteicon, div.choice, div.rdgGrp"

	$(document).click(function(e) { 
    		if(!$(e.target).closest(noteIcon).length) {
        		$('#showNote').removeClass("clicked");
    		}        
	});

	return this.click(function(e){
		$showNote = $("#showNote");
		$showNote.toggleClass("clicked");
		
	});
}

$.fn.hoverPopupNote = function() {
	/*** plugin to add a hover effect and popup note ***/
	$("<div id='showNote'>empty note</div>").appendTo("body").addClass("noDisplay");

	return this.hover(function(e){
		
		//the location of the note content has to be added to the find method
		var noteContent = $(this).find("div.note, div.corr, span.altRdg").html();
		
		$showNote = $("#showNote");
		$showNote.removeClass("clicked")
		
		$showNote.html(noteContent);
		$showNote.css({
			"position": "absolute",
			"top": e.pageY + 5,
			"left": e.pageX + 5,
		}).removeClass("noDisplay");
		
		
	}, function(e){
		/* on hover out hide the note */
		$("#showNote").addClass("noDisplay");
	});
};

/***** END Functionality related to popup notes *****/

/***** Functionality apparatus/line matching *****/

$.fn.matchAppHover = function() {
	/*** plugin that adds a apparatus matching functionality ***/
		this.hover(function(){
			var app = $(this).attr("data-app-id");
			$("."+app).addClass("matchAppHi");
		},function(){
			var app = $(this).attr("data-app-id");
			$("."+app).removeClass("matchAppHi");
		});
};
$.fn.matchAppClick = function() {
	/*** plugin that adds a line matching functionality ***/
		this.click(function(){
			var app = $(this).attr("data-app-id");
			$("."+app).toggleClass("matchAppHiClicked");
		});
};
$.fn.matchLineHover = function() {
	/*** plugin that adds a apparatus matching functionality ***/
		this.hover(function(){
            var line = $(this).closest("div.lineWrapper").attr("data-line-id");
			$("."+line).closest("div.lineWrapper").addClass("matchLineHi");
			$("#notesPanel .position."+line).parent(".noteContent").addClass("matchLineHi");
		},function(){
			var line = $(this).closest("div.lineWrapper").attr("data-line-id");
			$("."+line).closest("div.lineWrapper").removeClass("matchLineHi");
			$("#notesPanel .position."+line).parent(".noteContent").removeClass("matchLineHi");
		});
};
$.fn.matchLineClick = function() {
	/*** plugin that adds a line matching functionality ***/
		this.click(function(){
			var line = $(this).closest("div.lineWrapper").attr("data-line-id");
			$("."+line).closest("div.lineWrapper").toggleClass("matchLineHiClicked");
			$("#notesPanel .position."+line).parent(".noteContent").toggleClass("matchLineHiClicked");
		});
};
/***** END Functionality apparatus/line matching *****/

/***** Functionality audio player and audio-text matching *****/
$.fn.audioMatch = function() {
		
		/**app to add **/
		this.mousedown(function(){
				
				var timeStart = $(this).attr("data-timeline-start");
				var timeInterval = $(this).attr("data-timeline-interval");
				
				$(this).closest(".mssPanel").find("audio").each(function(){
					var $audio = $(this);
					
					if( $audio.prop('currentTime') === 0){
						$audio.trigger('play');
					}
					else{
					
					$audio.prop("currentTime",timeStart);
					$audio.trigger('play');
					}
						
				});
		});
};

/***** END Functionality related to audio player and audio-text matching *****/

/***** Initial setup of panels *****/

$.fn.bibPanel = function() {
	/*** Plugin responsible for the initial setup of bibPanel (visible: yes/no) 
	Plugin adds also click and hover effects to panel
	***/
	var keyword = "bibPanel";
	$("#"+keyword).appendTo(this);
	if(INITIAL_DISPLAY_BIB_PANEL){
		//bibPanel visible, constant INITIAL_DISPLAY_BIB_PANEL can be found in settings.xsl
		// $("#"+keyword).changePanelVisibility("-1px", panelPos);
        $("#"+keyword).changePanelVisibility(0, 10);

        $("nav *[data-panelid='"+ keyword +"']").toggleOnOffButton();
	}
	$("#"+keyword).panelClick();
	$("#"+keyword).panelHover();
}

$.fn.notesPanel = function() {
	/*** Plugin responsible for the initial setup of notesPanel (visible: yes/no) 
	Plugin adds also click and hover effects to panel
	***/
	var keyword = "notesPanel";
	$("#"+keyword).appendTo(this);
	if(INITIAL_DISPLAY_NOTES_PANEL){
		//notesPanel visible, constant INITIAL_DISPLAY_NOTES_PANEL can be found in settings.xsl
		// $("#"+keyword).changePanelVisibility("-1px", panelPos);
        $("#"+keyword).changePanelVisibility(0, 10);

        $("nav *[data-panelid='"+ keyword +"']").toggleOnOffButton();
		$("#mssArea .noteicon").toggle();
	}
	$("#"+keyword).panelClick();
	$("#"+keyword).panelHover();
}

$.fn.critPanel = function() {
	/*** Plugin responsible for the initial setup of critPanel (visible: yes/no) 
	Plugin adds also click and hover effects to panel
	***/
	var keyword = "critPanel";
	$("#"+keyword).appendTo(this);
	if(INITIAL_DISPLAY_CRIT_PANEL){
		//critPanel visible, constant INITIAL_DISPLAY_CRIT_PANEL can be found in settings.xsl
		// $("#"+keyword).changePanelVisibility("-1px", panelPos);
        $("#"+keyword).changePanelVisibility(0, 10);

        $("nav *[data-panelid='"+ keyword +"']").toggleOnOffButton();
	}	
	$("#"+keyword).panelClick();
	$("#"+keyword).panelHover();
}



$.fn.linenumber = function (){
	/*** Plugin responsible for the initial setup line numbers (on/off) ***/
	keyword = "linenumber";
	if(INITIAL_DISPLAY_LINENUMBERS){
		//line numbers visible, constant INITIAL_DISPLAY_LINENUMBERS can be found in settings.xsl
		$(".linenumber").toggleClass("noDisplay");
	}
	
}

$.fn.mssPanels = function (){
	/*** Plugin responsible for the initial setup of the manuscript panels (mssPanel) 
	Plugin adds click and hover effects to panels
	***/
	
	$(".facs-images, .pagebreak").each(function(){
		var $ele = $(this);
		var mssPanel = $(this).closest(".mssPanel")[0];	
		var mssId = $(mssPanel).attr("id");	
		var showElement = false;
		//if the facs-images or pagebreak has the same class as the panel ID
		if ($ele.hasClass(mssId)) {
			showElement = true;
			};
		if(!showElement){
			$ele.hide();
		}
	});
	//manuscript panels visible, constant INITIAL_DISPLAY_NUM_VERSIONS can be found in settings.xsl
	var versions = INITIAL_DISPLAY_NUM_VERSIONS;
	$("#versionList li").each(function(idx){
		var wit = $(this).attr("data-panelid");
		if(idx < versions){
			$("#"+wit).changePanelVisibility(0, 0);
			$("*[data-panelid='"+wit+"']").toggleOnOffButton();
		}
	});
	//add functionality to manuscript panels
	$(".mssPanel").panelClick();
	$(".mssPanel").panelHover();
	
	$(".mssPanel .panelBanner a").css({"color":"white", "text-decoration":"none"});
	
	
	
}
/***** END initial setup of panels  *****/



/***** DOCUMENT READY: INITIALIZE PLUGINS ******/

$(document).ready(function() {  
	
	/***** init panels and visibility *****/
	$("#mssArea").bibPanel();
	$("#mssArea").mssPanels();
	$("#mssArea").notesPanel();
	$("#mssArea").critPanel();
	$("#mssArea").linenumber();

	//after the visibility of all necessary panels is changed the workspace/mssArea has to be resized to fit panels
	$("#mssArea").panelResize();
	
	/*****END init panel and visibility *****/
	
	/***** activate all plugins *****/
	//close panel via X sign 
	$(".closePanel").closeButtonClick();
	
	//dropdown functionality
	$("#selectVersion").versionMenu();
	
	//click and hover event for panel buttons
	$("li[data-panelid]").panelButtonClick();
	$("li[data-panelid]").panelButtonHover();
	
	//click event to display and hide linen numbers
	$("#linenumberOnOff").linenumberOnOff();
	
	//create popup for note, choice, etc.
	$("div.noteicon, div.choice, div.rdgGrp").hoverPopupNote();
	$("div.noteicon, div.choice, div.rdgGrp").clickPopupNote();
	
	//adds match line/apparatus highlighting plugin
	$(".apparatus").matchAppHover();
	$(".apparatus").matchAppClick();
	//adds match audio with transcription plugin
	$(".audioReading").audioMatch();
	
	$("div.linenumber").matchLineClick();
	$("div.linenumber").matchLineHover();
	
	/**add draggable and resizeable to all panels (img + mss)*/
	$( ".panel" ).draggable({
		containment: "parent",
		zIndex: 6, 
		cancel: ".textcontent, .zoom-range, .bibContent, .noteContent, .critContent"
	}).resizable(
	{helper: "ui-resizable-helper"}
	);
		
	/**add functionality to image panels*/
	$(".imgPanel").zoomPan();
	$(".imgPanel").imgPanelHover();
	$(".imgPanel").imgPanelMousedown();
	$(".imgLink").imgLinkClick();
	$(".imgLink").imgLinkHover();
	
});
