<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
    xmlns:xs="http://www.w3.org/2001/XMLSchema"
    exclude-result-prefixes="xs"
    version="1.0">

  <!-- IMPORT DRUPAL SETTINGS -->
  <xsl:include href="drupal_settings.xsl" />

  <!-- include files in vm-images folder -->
  <xsl:variable name="vmLogo"><xsl:value-of select="$vmImages"/><xsl:text>gms_logo.png</xsl:text></xsl:variable>
  <xsl:variable name="menuArrowUp"><xsl:value-of select="$vmImages"/><xsl:text>arrowup.png</xsl:text></xsl:variable>
  <xsl:variable name="menuArrowDown"><xsl:value-of select="$vmImages"/><xsl:text>arrowdown.png</xsl:text></xsl:variable>
  <xsl:variable name="closePanelButton"><xsl:value-of select="$vmImages"/><xsl:text>closePanel.png</xsl:text></xsl:variable>
  <xsl:variable name="imageIcon"><xsl:value-of select="$vmImages"/><xsl:text>image.png</xsl:text></xsl:variable>
  <xsl:variable name="bannerImg"><xsl:value-of select="$vmImages"/><xsl:text>HeaderBackground.png</xsl:text></xsl:variable>
  
  <!-- include file form src folder -->
  <xsl:variable name="cssInclude">../src/vmachine.css</xsl:variable>
  <xsl:variable name="cssJQuery-UI">../src/js/jquery-ui-1.11.3/jquery-ui.min.css</xsl:variable>
    
  <!-- The JavaScript include file. -->  
  <xsl:variable name="jsInclude">../src/vmachine.js</xsl:variable>
      
  <!-- JQuery include files -->  
  <xsl:variable name="jsJquery">../src/js/jquery-1.11.2.min.js</xsl:variable>   
  <xsl:variable name="jsJquery-UI">../src/js/jquery-ui-1.11.3/jquery-ui.min.js</xsl:variable>
  
  <!-- ZoomPan files -->
  
  <xsl:variable name="cssJQueryZoomPan">../src/panzoom/panzoom.css</xsl:variable>
  <xsl:variable name="jsJqueryZoomPan">../src/panzoom/jquery.panzoom.min.js</xsl:variable>
    
  <!-- VM initial setup modifications -->
  <!-- NOTES PANEL: To change the VM so that the notes panel page does not
    appear at the initial load, change the below variable value from "true" to "false" below -->
    <xsl:variable name="displayNotes">false</xsl:variable>
  
  <!-- BIB PANEL: To change the VM so that the bibliographic information page does not
    appear at the initial load, change the below variable value from "true" to "false" below -->
    <xsl:variable name="displayBibInfo">false</xsl:variable>
  
  <!-- The number of version/witness panels to be displayed initially can be modified by changing the number below -->
  <xsl:variable name="displayVersions">2</xsl:variable>
  
  <!-- CRIT PANEL: Critical information should be encoded as tei:notesStmt/tei:note[@type='critIntro'] in the TEI files
    To change the VM so that the critical information page does not appear at the initial load 
    change the variable value from "true" to "false" -->
  <xsl:variable name="displayCritInfo">false</xsl:variable>
  
  <!-- To change the VM so that line numbers are hidden by default, change the variable below from
       "true" to "false" -->
  <xsl:variable name="displayLineNumbers">true</xsl:variable>
  
    
</xsl:stylesheet>