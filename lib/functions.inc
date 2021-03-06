<?php
require_once("script_begin.inc");
require_once("posts.inc");
require_once("portfolio.inc");

function display_header(){

				$phrases = array();
				$phrases[] = "[Try, Fail, Learn, Repeat]";
				$phrases[] = "[Jack of all trades, master at none]";
				$phrases[] = "[A small victory is still progress]";
				
				$phrase_count = count($phrases);
				$random = rand(0, $phrase_count-1);
				
				$phrase = $phrases[$random];
?>
    <div class="row-fluid home-header">
        <div class="row-fluid">
            <div class="span6" id="header-name">
                <h1 class="site-header"><a href="http://www.thebrockellis.com">The Brock Ellis</a></h1>
																<h3 class="sub-header"><?php echo $phrase ?></h3>
            </div>
            <div class="span6">
                <div id="left-menu">
                    <ul>
                        <li><a href="/blog">Blog</a></li>
                        <li><a href="portfolio">Portfolio</a></li>
                        <li><a href="about">About</a></li>
                        <li><a href="contact">Contact</a></li>
                    </ul>
                </div>              
            </div>
        </div>
    </div>  
<?php
}

function get_recent_posts(){
    $sql = "SELECT PostID FROM Posts ORDER BY Created DESC LIMIT 2";
    $rs = mysql_query($sql);
    if($rs) $rsc = mysql_num_rows($rs);
    if($rsc > 0){
        for($i=0; $i < $rsc; $i++){
            $postid = mysql_result($rs, $i, "postid");
            $po = new PostObj($postid);
            
?>
            
            <div class="media">
                <a class="pull-left" href="blog.php?postid=<?php echo $po->postid; ?>">
                <img class="media-object img-polaroid recent-image" src="<?php echo $po->image; ?>">
                </a>
                <div class="media-body">
                    <h4 class="media-heading"><?php echo stripslashes( $po->title ); ?></h4>
                    <p><?php echo substr($po->content, 0, 300) . "..."; ?></p>
                </div>
            </div>
            
<?php
            
        }  
    }
}


function display_footer(){
?>
    <hr>
    <footer style="text-align: center;">
        <ul class="footer">
            <li>&copy; 2013 Sharproot Media</li>
            <li><a href="blog/index">Blog</a></li>
            <li><a href="portfolio">Porfolio</a></li>
            <li><a href="about">About</a></li>
            <li><a href="contact">Contact</a></li>
        </ul>
    </footer>
<?php
}

function protect($string){
    $string = trim(strip_tags(addslashes($string)));
    return $string;
}

function admin_get_posts(){
?>
    <TABLE id="admin-post-table" class="table table-striped">
        <thead>
            <th>Post ID</th>
            <th></th>
            <th>Title</th>
            <th>Created</th>
            <th></th>
            <th></th>
        </thead>
        <tbody>
<?php
  
    $sql = "SELECT PostID FROM Posts ORDER BY PostID DESC";
    $rs = mysql_query($sql);
    if($rs) $rsc = mysql_num_rows($rs);
    if($rsc > 0){
        for($i=0; $i < $rsc; $i++){
            $postid = mysql_result($rs, $i, "PostID");
            $po = new PostObj($postid);
?>
            <TR id="row<?php echo $po->postid; ?>">
                <TD><?php echo $po->postid; ?></TD>
                <TD><a href="#uploadimage" data-toggle="modal" class="sss" id="<?php echo $postid; ?>"><i class="icon-camera"></i></a> </TD>
                <TD><?php echo $po->title; ?></TD>
                <TD><?php echo $po->created; ?></TD>
                <TD><a href="#editpost" data-toggle="modal" class="editpost" id="<?php echo $postid; ?>"><i class="icon-pencil"></i></a></TD>
                <TD><a class="deletepostbutton" id="<?php echo $po->postid; ?>" href="#"><i class="icon-remove"></i></a></TD>
            </TR>
<?php    
        }
    }
?>    
  
        </tbody>
    </TABLE>
    
    <div id="newpost" class="modal hide fade" role="dialog" aria-labelledby="myModalLabel" aria-hidden="true">
        <FORM id="newpost_form">
        <input type="hidden" id="secret" value="ansleigh12812" />   
        <div class="modal-header">
            <button type="button" class="close" data-dismiss="modal" aria-hidden="true">X</button>
            <h3 id="myModalLabel">New Post</h3>
        </div>
        <div class="modal-body">
                <label for="newpost_title">Title</label>
                <input type="text" id="newpost_title" name="newpost_title" value="" />
                <br />
                
                <label for="newpost_slug">Slug</label>
                <input type="text" id="newpost_slug" name="newpost_slug" value="" />
                <br />
        
                <label for="newpost_content">Content</label>
                <textarea class="post_content" id="newpost_content" name="newpost_content"></textarea>
        </div>
        <div class="modal-footer">
            <button class="btn" data-dismiss="modal" aria-hidden="true">Close</button>
            <button class="btn btn-primary" type="submit">Create Post</button>
        </div>
        </FORM>
    </div>
    
    <div id="editpost" class="modal hide fade" tabindex="-1" role="dialog" aria-labelledby="myModalLabel" aria-hidden="true">
        <FORM id="editpost_form">
        <input type="hidden" name="secret" value="ansleigh12812" />   
        <input type="hidden" id="editpost_id" value="" />
        <div class="modal-header">
            <button type="button" class="close" data-dismiss="modal" aria-hidden="true">X</button>
            <h3 id="myModalLabel">Edit Post</h3>
        </div>
        <div class="modal-body">
                <label for="editpost_title">Title</label>
                <input type="text" id="editpost_title" name="editpost_title" value="" />
                <br />
                
                <label for="editpost_slug">Slug</label>
                <input type="text" id="editpost_slug" name="editpost_slug" value="" />
                <br />
        
                <label for="editpost_content">Content</label>
                <textarea class="post_content" id="editpost_content" name="editpost_content"></textarea>
        </div>
        <div class="modal-footer">
            <button class="btn" data-dismiss="modal" aria-hidden="true">Close</button>
            <button class="btn btn-primary" type="submit">Edit Post</button>
        </div>
        </FORM>
    </div>
    
    <div id="uploadimage" class="modal hide fade" tabindex="-1" role="dialog" aria-labelledby="myModalLabel" aria-hidden="true">
        <FORM id="uploadimage_form" action="admin.php?task=uploadimage" method="POST" enctype="multipart/form-data">
        <input type="hidden" id="uploadimage_postid" name="uploadimage_postid" value="" />
        <div class="modal-header">
            <button type="button" class="close" data-dismiss="modal" aria-hidden="true">X</button>
            <h3 id="myModalLabel">Upload Image</h3>
        </div>
        <div class="modal-body">        
                <label for="file">Image (125x125) </label>
                <input type="file" id="file" name="file" />
        </div>
        <div class="modal-footer">
            <button class="btn" data-dismiss="modal" aria-hidden="true">Close</button>
            <button class="btn btn-primary" type="submit">Upload Image</button>
        </div>
        </FORM>
    </div>
    
    <SCRIPT type="text/javascript">
        $('document').ready(function(){            

            $('#newpost_content').wysihtml5();
   
            $('.editpost').on("click", function(){
                var postid = $(this).attr('id'); 
                var url = "/blog/post/data/" + postid;
                $.ajax({
                    url: url,
                    success: function(data){
                        //console.log(data);
                        var obj = jQuery.parseJSON(data);
                        //console.log(obj.post[0].Content);
                        $('#editpost_id').val(obj.post[0].PostID);
                        $('#editpost_title').val(obj.post[0].Title);
                        $('#editpost_content').val(obj.post[0].Content);
                        $('#editpost_slug').val(obj.post[0].Slug);
                        
                        var already = $('div#editpost input[name="_wysihtml5_mode"]').val();
                        //alert(already);
                        if(already != 1) $('#editpost_content').wysihtml5();
                    }
                }); //ajax
            }); //on click
            
            $('#editpost_form').submit(function(event){
                event.preventDefault();
                
                var postid = $("#editpost_id").val();
                var url = "blog/post/data/" + postid; 
                var data = $(this).serialize(); //alert(data);
                $.ajax({
                    url: url,
                    data: data,
                    type: 'PUT',
                    success: function(result) {
                        $('#editpost').modal('toggle');
                        location.href = "admin.php";
                    },
                    error: function(result) {
                        alert("FAIL" + result);
                    }
                }); //ajax
            }); //on submit
            
            $('.deletepostbutton').on("click", function(){
                if(confirm("You're about to delete a post. Are you sure?")){
                    var postid = $(this).attr('id');
                    var url = "blog/post/data/" + postid
                    $.ajax({
                        url: url,
                        data: "secret=ansleigh12812",
                        type: 'DELETE',
                        success: function(result) {
                            $('#row' + postid).hide();
                        },
                        error: function(result) {
                            //alert("FAIL");
                        }
                    });
                } //if confirm
            }); //on click
            
            $('#newpost_form').submit(function(event){
                event.preventDefault();
                var url = "blog/post/data";
                var data = $(this).serialize();
                $.ajax({
                    url: url,
                    data: data,
                    type: 'POST',
                    success: function(result) {
                        $('#newpost').modal('toggle');
                        location.href = "admin.php";
                    },
                    error: function(result) {
                        alert("FAIL" + result);
                    }
                }); //ajax
            }); //on submit
            
            $('.sss').on("click", function(){
                var postid = $(this).attr('id');
                //alert("PostID: " + postid);
                $('#uploadimage_postid').val(postid); 
            }); //on click
            
            /*$('#uploadimage_form').submit(function(event){
                event.preventDefault();
                alert("Getting here");
                var url = "../admin.php?task=uploadimage";
                //var data = $(this).serialize();
                $.ajax({
                    url: url,
                    data: { 
                        postid: $("#uploadimage_postid").val(),
                        file: $("#file").val()
                    },
                    type: 'POST',
                    success: function(result) {
                        $('#uploadimage').modal('toggle');
                        //location.href = "admin.php";
                    },
                    error: function(result) {
                        alert("FAIL" + result);
                    }
                }); //ajax
            }); //on submit*/
            
        }); //doc ready
    </SCRIPT>
    
<?php
    
}

function admin_get_contact(){
    
}


 /******************************************************
 * TORO SPECIFIC FUNCTIONS
 *****************************************************/
function get_posts(){
    $data = array();
    $sql = "SELECT p.*, COUNT(pc.PostCommentID) AS Count FROM Posts p LEFT JOIN PostComments pc ON p.PostID = pc.PostID GROUP BY p.PostID ORDER BY p.PostID DESC";
    error_log("SQL: $sql");
    $rs = mysql_query($sql);
    while($row = mysql_fetch_assoc($rs)) {
       $data[] = $row;
    }
    return($data);
}

function get_post_by_slug($slug) {
    $data = array();
    $sql = "SELECT * FROM Posts WHERE Slug = '$slug' ";
    //error_log($sql);
    $rs = mysql_query($sql);
    $rs = mysql_fetch_assoc($rs);
    return($rs);
}

function get_post_comments($postid) {
    $data = array();
    $sql = "SELECT * FROM PostComments WHERE PostID = $postid ORDER BY Created ASC";
    $rs = mysql_query($sql);
    while($row = mysql_fetch_assoc($rs)) {
       $data[] = $row;
    }
    return($data);
}

function save_comment($postid, $name, $comment) {
    $sql = "INSERT INTO PostComments (";
    $sql .= "PostID, Name, Comment";
    $sql .= ")VALUES(";
    $sql .= "$postid, '$name', '$comment'";
    $sql .= ")";
    error_log("Insert comment: $sql");
    $rs = mysql_query($sql);
}

function get_post_data($postid){
    $sql = "SELECT * FROM Posts WHERE PostID = $postid";
    $rs = mysql_query($sql);
        
    $rows = array();
    while($r = mysql_fetch_assoc($rs)) {
      	$rows['post'][] = $r;
    }
 
    return($rows);
}

function get_posts_data(){
    $sql = "SELECT * FROM Posts";
    $rs = mysql_query($sql);
        
    $rows = array();
    while($r = mysql_fetch_assoc($rs)) {
      	$rows['posts']['post'][] = $r;
    }
 
    return($rows);
}
 
function display_portfolio(){
    $type_array = array(
        1 => "Website",
        2 => "Application",
        3 => "Media",
        4 => "Misc"
    );

    $sql = "SELECT Title, Description, Image, Type, Link, ";
    $sql .= "DATE_FORMAT(Created, '%m/%e/%Y') as Date ";
    $sql .= "FROM Portfolio ";
    if($type) $sql .= "WHERE Type = $type";
    error_log("SQL: $sql");
    $rs = mysql_query($sql);
    if($rs) $rsc = mysql_num_rows($rs);
    if($rsc > 0){
    for($i=0; $i < $rsc; $i++){
        $title = mysql_result($rs, $i, "Title");
        $desc = mysql_result($rs, $i, "Description");
        $image = mysql_result($rs, $i, "Image");
        $type = mysql_result($rs, $i, "Type");
        $link = mysql_result($rs, $i, "Link");
        $date = mysql_result($rs, $i, "Date");

?>
    <div class="portfolio-box">
        <img class="portfolio-image" src="http://lorempixel.com/600/100" alt="<?php echo $title; ?>" />
        <div class="portfolio-text">
            <h4><a href="http://<?php echo $link; ?>"><?php echo $title; ?></a></h4>
            <p><?php echo $desc; ?></p>
            <div class"portfolio-details">
                <p><i class="icon-filter icon-white"></i> <?php echo $type_array[$type]; ?> | <i class="icon-calendar icon-white"></i> <?php echo $date; ?></p>
            </div>
            <div class="portfolio-overlay">
                <a href="http://<?php echo $link; ?>" alt="<?php echo $title; ?>" class="portfolio-view">View Now!</a>
            </div>
        </div>
    </div>
<?php
    } //end is rsc > 0
    } //end for loop
}

function admin_get_portfolio(){
?>
    <TABLE id="admin-portfolio-table" class="table table-striped">
        <thead>
            <th>Portfolio ID</th>
            <th></th>
            <th>Title</th>
            <th>Created</th>
            <th>Type</th>
            <th></th>
            <th></th>
        </thead>
        <tbody>
<?php
  
    $sql = "SELECT PortfolioID FROM Portfolio ORDER BY PortfolioID DESC";
    $rs = mysql_query($sql);
    if($rs) $rsc = mysql_num_rows($rs);
    if($rsc > 0){
        for($i=0; $i < $rsc; $i++){
            $portfolio = mysql_result($rs, $i, "PortfolioID");
            $po = new PortfolioObj($portfolioid);
?>
            <TR id="row<?php echo $po->portfolioid; ?>">
                <TD><?php echo $po->portfolioid; ?></TD>
                <TD><a href="#uploadimage" data-toggle="modal" class="sss" id="<?php echo $portfolioid; ?>"><i class="icon-camera"></i></a> </TD>
                <TD><?php echo $po->title; ?></TD>
                <TD><?php echo $po->created; ?></TD>
                <TD><?php echo $po->type; ?></TD>
                <TD><a href="#editpost" data-toggle="modal" class="editpost" id="<?php echo $portfolioid; ?>"><i class="icon-pencil"></i></a></TD>
                <TD><a class="deleteportfoliobutton" id="<?php echo $po->portfolioid; ?>" href="#"><i class="icon-remove"></i></a></TD>
            </TR>
<?php    
        }
    }
?>    
  
        </tbody>
    </TABLE>
    
    <div id="newportfolio" class="modal hide fade" role="dialog" aria-labelledby="myModalLabel" aria-hidden="true">
        <FORM id="newportfolio_form">
        <input type="hidden" id="secret" value="ansleigh12812" />   
        <div class="modal-header">
            <button type="button" class="close" data-dismiss="modal" aria-hidden="true">X</button>
            <h3 id="myModalLabel">New Portfolio</h3>
        </div>
        <div class="modal-body">
                <label for="newportfolio_title">Title</label>
                <input type="text" id="newportfolio_title" name="newportfolio_title" value="" />
                <br />
                
                <label for="newportfolio_type">Type</label>
                <select id="newportfolio_type" name="newportfolio_type">
                    <option value=1>Website</option>
                    <option value=2>Application</option>
                    <option value=3>Media</option>
                    <option value=4>Misc</option>
                </select>
                <br />
        
                <label for="newportfolio_description">Description</label>
                <textarea class="newportfolio_description" id="newportfolio_description" name="newportfolio_description"></textarea>
        </div>
        <div class="modal-footer">
            <button class="btn" data-dismiss="modal" aria-hidden="true">Close</button>
            <button class="btn btn-primary" type="submit">Create Portfolio</button>
        </div>
        </FORM>
    </div>
    
    <div id="editportfolio" class="modal hide fade" tabindex="-1" role="dialog" aria-labelledby="myModalLabel" aria-hidden="true">
        <FORM id="editportfolio_form">
        <input type="hidden" name="secret" value="ansleigh12812" />   
        <input type="hidden" id="editportfolio_id" value="" />
        <div class="modal-header">
            <button type="button" class="close" data-dismiss="modal" aria-hidden="true">X</button>
            <h3 id="myModalLabel">Edit Portfolio</h3>
        </div>
        <div class="modal-body">
                <label for="editportfolio_title">Title</label>
                <input type="text" id="editportfolio_title" name="editportfolio_title" value="" />
                <br />
                
                <label for="editportfolio_type">Type</label>
                <input type="text" id="editportfolio_type" name="editportfolio_type" value="" />
                <br />
        
                <label for="editportfolio_description">Description</label>
                <textarea class="editportfolio_description" id="editportfolio_description" name="editportfolio_description"></textarea>
        </div>
        <div class="modal-footer">
            <button class="btn" data-dismiss="modal" aria-hidden="true">Close</button>
            <button class="btn btn-primary" type="submit">Edit Portfolio</button>
        </div>
        </FORM>
    </div>
    
    <div id="portfolio_uploadimage" class="modal hide fade" tabindex="-1" role="dialog" aria-labelledby="myModalLabel" aria-hidden="true">
        <FORM id="portfolio_uploadimage_form" action="admin.php?task=portfoliouploadimage" method="POST" enctype="multipart/form-data">
        <input type="hidden" id="uploadimage_portfolioid" name="uploadimage_portfolioid" value="" />
        <div class="modal-header">
            <button type="button" class="close" data-dismiss="modal" aria-hidden="true">X</button>
            <h3 id="myModalLabel">Upload Image</h3>
        </div>
        <div class="modal-body">        
                <label for="file">Image (125x125) </label>
                <input type="file" id="file" name="file" />
        </div>
        <div class="modal-footer">
            <button class="btn" data-dismiss="modal" aria-hidden="true">Close</button>
            <button class="btn btn-primary" type="submit">Upload Image</button>
        </div>
        </FORM>
    </div>
    
    <SCRIPT type="text/javascript">
        $('document').ready(function(){            

            $('#newportfolio_content').wysihtml5();
   
            $('.editportfolio').on("click", function(){
                var portfolioid = $(this).attr('id'); 
                var url = "/admin.php?task=editportfolio&verb=get&portfoilioid" + portfolioid;
                $.ajax({
                    url: url,
                    success: function(data){
                        //console.log(data);
                        var obj = jQuery.parseJSON(data);
                        //console.log(obj.post[0].Content);
                        $('#editportfolio_id').val(obj.post[0].PortfolioID);
                        $('#editportfolio_title').val(obj.post[0].Title);
                        $('#editportfolio_description').val(obj.post[0].Description);
                        $('#editportfolio_type').val(obj.post[0].Type);
                        
                        var already = $('div#editportfolio input[name="_wysihtml5_mode"]').val();
                        //alert(already);
                        if(already != 1) $('#editportfolio_content').wysihtml5();
                    }
                }); //ajax
            }); //on click
            
            $('#editportfolio_form').submit(function(event){
                event.preventDefault();
                
                var portfolioid = $("#editportfolio_id").val();
                var url = "admin.php?task=editportfolio&verb=put&portfolioid=" + portfolioid; 
                var data = $(this).serialize(); //alert(data);
                $.ajax({
                    url: url,
                    data: data,
                    success: function(result) {
                        $('#editportfolio').modal('toggle');
                        location.href = "admin.php";
                    },
                    error: function(result) {
                        alert("FAIL" + result);
                    }
                }); //ajax
            }); //on submit
            
            $('.deleteportfoliobutton').on("click", function(){
                if(confirm("You're about to delete a portfolio item. Are you sure?")){
                    var portfolioid = $(this).attr('id');
                    var url = "admin.php?task=editportfolio&verb=delete&portfolioid=" + portfolioid
                    $.ajax({
                        url: url,
                        data: "secret=ansleigh12812",
                        success: function(result) {
                            $('#row' + portfolioid).hide();
                        },
                        error: function(result) {
                            //alert("FAIL");
                        }
                    });
                } //if confirm
            }); //on click
            
            $('#newportfolio_form').submit(function(event){
                event.preventDefault();
                var url = "admin.php?task=editportfolio&verb=insert";
                var data = $(this).serialize();
                $.ajax({
                    url: url,
                    data: data,
                    success: function(result) {
                        $('#newportfolio').modal('toggle');
                        location.href = "admin.php";
                    },
                    error: function(result) {
                        alert("FAIL" + result);
                    }
                }); //ajax
            }); //on submit
            
            $('.sss').on("click", function(){
                var portfolioid = $(this).attr('id');
                //alert("PortfolioID: " + portfolioid);
                $('#uploadimage_portfolioid').val(portfolioid); 
            }); //on click
            
        }); //doc ready
    </SCRIPT>
    
<?php
    }
    
function contact_sidebar(){
    ?>
    <img src="assets/thebrockellis.jpg" id="portrait" title="Self portrait" class="img-circle img-polaroid" />
    <h2 id="acm">Other Ways <br />To Talk To Me</h2>
    
    <div class="contact_icon" id="contact_facebook">
        <a href="http://www.facebook.com/thebrockellis">
            <img src="assets/facebook.png" title="Facebook" /> 
           </a>  
    </div>
    
    <div class="contact_icon" id="contact_twitter">
        <a href="http://www.twitter.com/thebrockellis">
            <img src="assets/twitter.png" title="Twitter" />
           </a>
    </div>
    
    <div class="clear"></div>
    
    <div class="contact_icon" id="contact_github">
        <a href="http://www.github.com/thebrockellis">
            <img src="assets/github.png" title="Github" />
           </a>
    </div>
    
    <div class="contact_icon" id="contact_youtube">
        <a href="http://www.youtube.com/thebrockellis" title="YouTube" />
            <img src="assets/youtube.png" title="YouTube" />
        </a>
    </div>
    
    <h3>Latest Tweets</h3>
    <p>Tweet</p>    <p>Tweet</p>    <p>Tweet</p>    <p>Tweet</p>
    <?
}

?>
