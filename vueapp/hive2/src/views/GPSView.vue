<template>
    <div>
        <div class="container-fluid" >
            <div class="row">
                <div class="col-8">
                    <div class="map-responsive">
                        <iframe style="position: absolute;"
                            height = "60%"
                            width= "100%"
                            loading="lazy"
                            allowfullscreen
                            src="https://www.google.com/maps/embed/v1/place?key=!!!API-KEY!!!
                                    &q=University+of+Wyoming,Laramie+WY">
                        </iframe>
                    </div>
                </div>
                <div class="col-4">
                    <div class="list-group" >
                        <a href="#" class="list-group-item list-group-item-action active" aria-current="true">
                            First Pin
                        </a>
                        <a href="#" class="list-group-item list-group-item-action">Second pin</a>
                        <a href="#" class="list-group-item list-group-item-action">Third Pin</a>
                        <a href="#" class="list-group-item list-group-item-action">Fourth Pin</a>
                        <a class="list-group-item list-group-item-action disabled">disabled Pin</a>
                    </div>
                </div>
            </div>
        </div>    
    </div>
</template>

<style scope>
.map-responsive{
    overflow:hidden;
    padding-bottom:67%;
    position:relative;
    height:0;
}
.map-responsive iframe{
    left:5%; 
    top:0;
    height:100%;
    width:100%;
    position:absolute;
}
</style>