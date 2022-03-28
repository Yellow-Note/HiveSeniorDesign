<template>
  <div class="home">
    <h1>Testing</h1>
    <img class="img-fluid" :src="image" alt="Side Bar Picture">

    <div class="mb-3">
      <label for="formFile" class="form-label">Import .MOV File</label>
      <input class="form-control" type="file" @change="importFile($event)">
      <div class="form-text">Select one ".MOV" file to import at a time.</div>
    </div>
    <div class="d-grid gap-2">
      <button class="btn btn-primary" type="button" @click="changeImage" >Change Image</button>
    </div>
    <!--<file-selector v-model="files">
      <dropzone v-slot
    </file-selector> -->
  </div>
</template>

<script>
const { ipcRenderer } = require('electron')
window.ipcRenderer = ipcRenderer

export default {
  name: 'HomeView',
  components: {
    
  },
  data() {
    return {
      images: ["@/assets/logo.png", "@/assets/images.png"],
      image: require("@/assets/logo.png")
    }
  },
  methods: {
    importFile(event){
      var result = 'none'
      if(event.target.files.length > 0) {
        var filePath = event.target.files[0].path
        /* eslint-disable no-unused-vars */
        
      }
      result = ipcRenderer.invoke('importfile', filePath).then(this.callAlert(result))

    },
    callAlert(message){
      alert(message)
    },
    changeImage() {
      this.image = require(this.images[1])
    }
  }
}
</script>
