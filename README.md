## Turnbull Names: Edges & Nodes
*Software: MIT License (2018) M. H. Beals*  
*Instructions: CC-BY 4.0 (2018) M. H. Beals*

### Instructions for use

#### Data Files
This programme utilises the data files of the Turnbull Names collection:

Alexander Turnbull Library, National Library of New Zealand Te Puna M?tauranga | Aotearoa, licensed by the Department of Internal Affairs for re-use under the Creative Commons Attribution 4.0 New Zealand Licence.

The latest version can be found here:(https://natlib.govt.nz/about-us/open-data/turnbull-names-metadata)

You can use the preproccess names lists included in this repository (5 March 2018) or create new ones using the included XSL transformation files and the online data set.

**Example XSL commands:**  

    java -jar saxon9he.jar -s:eac-full-extract\0\EAC-CPF-4.xml -o:ATLNamesList.txt -xsl:ATLNamesTransform_All.xsl
    java -jar saxon9he.jar -s:eac-full-extract\0\EAC-CPF-4.xml -o:ATLNamesListCreator.txt -xsl:ATLNamesTransform_CreatorContributor.xsl

#### Preparing a filter list
1. Open the full names list, **ATLNamesList.txt**, in your preferred spreadsheet or dataset management software.  I suggest using [OpenRefine](http://openrefine.org/), but Microsoft Excel or Open Office Sheets will work as well.

2. You may alternatively use the **ATLNamesListCreator.txt**, which does not include people mentioned or the subject of items (subjectOf), only Creators(creatorOf) and Contributors (other).

3. Filter the list to either you preferred set of publication IDs or person names.

4. Delete the person names so you have only a list of their associated publications.

5. Save the file as **ATLFilterList.txt**, making sure it is in the same directory/folder as **ATLNamesList.txt**.

An example filter list has been included for reference.

#### Running the Programme

1. Run the programme.  As an unsigned programme, you may receive a warning when running on Windows, which you can safely ignore (if you trust me).

2. At the prompt, enter the full path of the directory in which you included **ATLFilterList.txt** and **ATLNamesList.txt**. Make sure to include the final "\" at the end of the path.

3. Indicate whether you are using the full names list **(F)** or the contributor only list **(C)**.

When complete, you will have two new files:  

+ ATLEdges.csv
+ ATLNodes.csv

You can now import these into your preferred visualisation software, though they have been headed to work best with [Gephi](https://gephi.org/)

### Acknowledgements

This programme was developed during my visiting fellowship with Victoria University Wellington and the National Library of New Zealand, whom I would thank for their kind hosting during my research in April 2018.