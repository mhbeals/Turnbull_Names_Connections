<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet 
xmlns:xsl="http://www.w3.org/1999/XSL/Transform" 
xmlns:xs="http://www.w3.org/2001/XMLSchema"  
version="2.0" 
xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
xmlns:xlink="http://www.w3.org/1999/xlink" 
xpath-default-namespace="urn:isbn:1-931666-33-4"
exclude-result-prefixes="xlink xs xsi"
>

<xsl:output method="text" encoding="UTF-8" indent="yes"/>	


<xsl:template match="/">
	<xsl:for-each select="collection(concat('eac-full-extract/', '?select=*.xml;recurse=yes'))">
		<xsl:for-each select="eac-cpf">
			<xsl:for-each select="cpfDescription">
				<xsl:for-each select="relations">
					<xsl:for-each select="resourceRelation">						
							<xsl:for-each select="relationEntry">
								<xsl:value-of select="."/><xsl:text>&#x9;</xsl:text><xsl:value-of select="../../../identity/nameEntry[1]/part"/><xsl:text>&#xa;</xsl:text>
							</xsl:for-each>
					</xsl:for-each>
				</xsl:for-each>
			</xsl:for-each>
		</xsl:for-each>
	</xsl:for-each>
</xsl:template>

</xsl:stylesheet>


