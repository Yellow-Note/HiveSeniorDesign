<template>
    <div>
        <div class="container-fluid" >
            <div class="row">
                <div class="col-8">
                    <div class="map-responsive">
                        <GoogleMap class="map-responsive-googlemap" 
                        :lat="this.currentlat" :lng="this.currentlng"></GoogleMap>
                    </div>
                </div>
                <div class="col-4">
                    <div class="list-group">
                        <div v-for="data in datapoints" :key="data.imageName">
                            <div class="list-group-item list-group-item-action" @click="changePin(data, data.imageLocation)">{{data.imageName}}</div>
                        </div>
                        <button type="button" class="btn btn-primary">Manual Location</button>
                        <div>
                        </div>
                        <!--
                    <picture :key="currImageURL">
                        <source :src="currImageURL">
                    </picture>
                    -->
                    <div :key="currentImage">
                        <img :src="currentImage" width="460">
                    </div>
                    </div>
                </div>
            </div>
        </div>    
    </div>
</template>
<script>

import { array } from 'yargs'
import GoogleMap from '../components/GoogleMap.vue'
export default {
    components: {
        GoogleMap
    }, 
    props: {
        datapoints: {
            type: array,
            default: 
                [{
                imageLocation: 'C:/Users/pyrodraco/Desktop/COSC/SeniorProject/vueapp/hive2/public/images/Alerted/picture1.jpg',
                imageName: 'Pin Default Timestamp 99:99:99',
                lat: 41.1585,
                lng: -105.370
            }]
         },
    },
    computed: {
      currImageURL: function() {
          
          return this.currentImage
      }
    },
    data() {
        return {
            currentlat: 123.222,
            currentlng: 123.222,
            currentImage: "C:/Users/pyrodraco/Desktop/COSC/SeniorProject/vueapp/hive2/public/images/Alerted/picture1.jpg"
        }
    },
    
    methods: {
        changePin(data, imageURL){
            this.currentlat = data.lat
            this.currentlng = data.lng
            this.currentImage = imageURL
            return
        }
    }
    
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