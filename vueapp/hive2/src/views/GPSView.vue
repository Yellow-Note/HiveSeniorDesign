<template>
    <div>
        <div class="container-fluid" >
            <div class="row">
                <div class="col-8">
                    <div class="map-responsive">
                        <GoogleMap class="map-responsive-googlemap"></GoogleMap>
                    </div>
                </div>
                <div class="col-4">
                    <div class="list-group">
                        <button type="button" class="btn btn-primary">Manual Location</button>
                        <div>
                        <a href="#" class="list-group-item list-group-item-action" aria-current="true">
                            First Pin
                        </a>
                        <a href="#" class="list-group-item list-group-item-action">Second pin</a>
                        <a href="#" class="list-group-item list-group-item-action">Third Pin</a>
                        <a href="#" class="list-group-item list-group-item-action">Fourth Pin</a>
                        <a class="list-group-item list-group-item-action disabled">disabled Pin</a>
                        </div>
                    <img src="../assets/logo.png" alt="nope">
                    </div>
                </div>
            </div>
        </div>    
    </div>
</template>
<script>
import GoogleMap from '../components/GoogleMap.vue'
export default {
    components: {
        GoogleMap
    }, data() {
        return {
            
        }
    },
}


</script>


<style scope>
.map-responsive{
    overflow:hidden;
    padding-bottom:67%;
    position:relative;
    height:0;
}
.map-responsive-googlemap{
    left:5%; 
    top:0;
    height:100%;
    width:100%;
    position:absolute;
}
</style>